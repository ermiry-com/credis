#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/utils/log.h>

#include <hiredis/hiredis.h>

#include "redis.h"

static redisContext *redis_context = NULL;

static RedisStatus status = REDIS_STATUS_DISCONNECTED;

static unsigned int redis_port = 6379;
static char redis_host[REDIS_HOST_SIZE] = { 0 };

static struct timeval timeout = { 1, 500000 };

RedisStatus redis_get_status (void) { return status; }

void redis_set_hostname (const char *host) {

	if (host) {
		(void) strncpy (redis_host, host, REDIS_HOST_SIZE - 1);
	}

}

void redis_set_port (const unsigned int port) {

	redis_port = port;

}

// sets the connection timeout
// default to 1.5 seconds
void redis_set_timeout (const long seconds, const long miliseconds) {

	timeout.tv_sec = seconds;
	timeout.tv_usec = miliseconds * 1000;

}

// connects to the redis server
// returns 0 on success, 1 on error
unsigned int redis_connect (void) {

	unsigned int retval = 1;

	if (status == REDIS_STATUS_DISCONNECTED) {
		redisOptions o = { 0 };
		REDIS_OPTIONS_SET_TCP (&o, redis_host, redis_port);

		redis_context = redisConnectWithOptions (&o);

		if (redis_context) {
			if (redis_context->err) {
				cerver_log_error (
					"REDIS - connection error: %s",
					redis_context->errstr
				);

				redisFree (redis_context);
			}

			else {
				// success
				status = REDIS_STATUS_CONNECTED;
				retval = 0;
			}
		}

		else {
			cerver_log_error ("Failed to connect to redis!");
		}
	}

	else {
		cerver_log_warning ("Already connected to redis!");
	}

	return retval;

}

// disconnects from the redis server
// returns 0 on success, 1 on error
unsigned int redis_disconnect (void) {

	unsigned int retval = 1;

	if (redis_context) {
		if (status == REDIS_STATUS_CONNECTED) {
			// disconnects and frees the context
			redisFree (redis_context);
			redis_context = NULL;

			retval = 0;
		}
	}

	return retval;

}

// pings the db to test for a success connection
// returns 0 on success, 1 on error
unsigned int redis_ping_db (void) {

	unsigned int retval = 1;

	if (redis_context) {
		redisReply *reply = (redisReply *) redisCommand (redis_context, "PING");
		if (reply) {
			(void) fprintf (stdout, "\n[REDIS][PING]: %s\n", reply->str);
			freeReplyObject (reply);

			retval = 0;
		}
	}

	return retval;

}
