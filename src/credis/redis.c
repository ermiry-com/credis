#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hiredis/hiredis.h>

#include "credis/collections/pool.h"

#include "credis/client.h"
#include "credis/crud.h"
#include "credis/redis.h"

static Credis credis = {
	.hostname_len = 0,
	.hostname = { 0 },

	.port = REDIS_DEFAULT_PORT,

	.timeout = {
		.tv_sec = REDIS_DEFAULT_TIMEOUT_SECS,
		.tv_usec = REDIS_DEFAULT_TIMEOUT_MILI
	},

	.clients_pool_init = REDIS_DEFAULT_CLIENTS_POOL_INIT,
	.clients_pool = NULL
};

const char *credis_get_hostname (void) {

	return credis.hostname;

}

void credis_set_hostname (const char *host) {

	if (host) {
		(void) strncpy (credis.hostname, host, REDIS_HOST_SIZE - 1);
		credis.hostname_len = (unsigned int) strlen (credis.hostname);
	}

}

const unsigned int credis_get_port (void) {

	return credis.port;

}

void credis_set_port (const unsigned int port) {

	credis.port = port;

}

// sets the connection timeout
// default to 1.5 seconds
void credis_set_timeout (
	const long seconds, const long miliseconds
) {

	credis.timeout.tv_sec = seconds;
	credis.timeout.tv_usec = miliseconds * 1000;

}

void credis_set_clients_pool_init (
	const unsigned int clients_pool_init
) {

	credis.clients_pool_init = clients_pool_init;

}

CredisClient *credis_client_get (void) {

	return (CredisClient *) credis_pool_pop (credis.clients_pool);

}

void credis_client_return (CredisClient *client) {

	(void) credis_pool_push (credis.clients_pool, client);

}

static unsigned int credis_clients_pool_init (void) {

	unsigned int retval = 1;

	credis.clients_pool = credis_pool_create (redis_client_destroy);
	if (credis.clients_pool) {
		credis_pool_set_create (credis.clients_pool, credis_client_create);
		credis_pool_set_produce_if_empty (credis.clients_pool, true);
		if (!credis_pool_init (
			credis.clients_pool,
			credis_client_create,
			credis.clients_pool_init
		)) {
			retval = 0;
		}

		else {
			(void) fprintf (
				stderr,
				"[CREDIS][ERROR]: Failed to init clients pool!\n"
			);
		}
	}

	else {
		(void) fprintf (
			stderr,
			"[CREDIS][ERROR]: Failed to create clients pool!\n"
		);
	}

	return retval;

}

unsigned int credis_init (void) {

	unsigned int retval = 1;

	if (credis.hostname_len) {
		if (!credis_clients_pool_init ()) {
			retval = 0;
		}
	}

	return retval;

}

// pings the db to test for a success connection
// returns 0 on success, 1 on error
unsigned int credis_ping_db (void) {

	unsigned int retval = 1;

	CredisClient *client = credis_client_get ();
	if (client) {
		redisReply *reply = (redisReply *) redisCommand (
			client->redis_context, "PING"
		);

		if (reply) {
			(void) fprintf (stdout, "\n[CREDIS][PING]: %s\n", reply->str);
			freeReplyObject (reply);

			retval = 0;
		}

		credis_client_return (client);
	}

	return retval;

}

// sets a key "oki" - value "doki" pair
// to be used for testing
// returns 0 on success, 1 on error
unsigned int credis_set_test (void) {

	return credis_set ("oki", "doki");

}

// checks if the test key "oki" exists
// returns 0 on success, 1 on error
unsigned int credis_exists_test (void) {

	return credis_exists ("oki");

}

// removes the test key "oki"
// returns 0 on success, 1 on error
unsigned int credis_remove_test (void) {

	return credis_del ("oki");

}

void credis_end (void) {

	credis_pool_delete (credis.clients_pool);
	credis.clients_pool = NULL;

}
