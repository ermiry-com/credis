#include <stdlib.h>

#include "credis/client.h"
#include "credis/redis.h"

static unsigned int credis_client_connect (
	CredisClient *client
);

static unsigned int redis_disconnect (
	CredisClient *client
);

static CredisClient *credis_client_new (void) {

	CredisClient *client = (CredisClient *) malloc (sizeof (CredisClient));
	if (client) {
		client->status = REDIS_STATUS_DISCONNECTED;

		client->redis_options.connect_timeout = NULL;
		client->redis_options.command_timeout = NULL;

		client->redis_options.privdata = NULL;
		client->redis_options.free_privdata = NULL;

		client->redis_options.push_cb = NULL;
		client->redis_options.async_push_cb = NULL;

		client->redis_context = NULL;
	}

	return client;

}

static void credis_client_delete (void *client_ptr) {

	if (client_ptr) {
		CredisClient *client = (CredisClient *) client_ptr;

		if (client->redis_context) {
			redisFree (client->redis_context);
			client->redis_context = NULL;
		}

		free (client_ptr);
	}

}

// creates and connects a new credis client
void *credis_client_create (void) {

	CredisClient *client = credis_client_new ();

	if (client) {
		REDIS_OPTIONS_SET_TCP (
			&client->redis_options,
			credis_get_hostname (),
			credis_get_port ()
		);

		if (credis_client_connect (client)) {
			// failed to connect to redis
			credis_client_delete (client);
			client = NULL;
		}
	}

	return client;

}

void redis_client_destroy (void *client_ptr) {

	(void) redis_disconnect ((CredisClient *) client_ptr);
	credis_client_delete (client_ptr);

}

static unsigned int credis_client_connect (
	CredisClient *client
) {

	unsigned int retval = 1;

	if (client->status == REDIS_STATUS_DISCONNECTED) {
		client->redis_context = redisConnectWithOptions (
			&client->redis_options
		);

		if (client->redis_context) {
			if (client->redis_context->err) {
				(void) fprintf (
					stderr,
					"[CREDIS][ERROR]: Connection error - %s\n",
					client->redis_context->errstr
				);

				redisFree (client->redis_context);
			}

			else {
				// success
				client->status = REDIS_STATUS_CONNECTED;
				retval = 0;
			}
		}

		else {
			(void) fprintf (
				stderr,
				"[CREDIS][ERROR]: Failed to connect to redis!\n"
			);
		}
	}

	else {
		(void) fprintf (
			stderr,
			"[CREDIS][ERROR]: Already connected to redis!\n"
		);
	}

	return retval;

}

static unsigned int redis_disconnect (
	CredisClient *client
) {

	unsigned int retval = 1;

	if (client->redis_context) {
		if (client->status == REDIS_STATUS_CONNECTED) {
			// disconnects and frees the context
			redisFree (client->redis_context);
			client->redis_context = NULL;

			retval = 0;
		}
	}

	return retval;

}
