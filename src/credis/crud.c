#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>

#include <hiredis/hiredis.h>

#include "credis/client.h"
#include "credis/redis.h"

// issues a command to Redis
// returns 0 on success, 1 on error
unsigned int credis_command (const char *format, ...) {

	unsigned int retval = 1;

	if (format) {
		va_list args;
		va_start (args, format);

		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisvCommand (
				client->redis_context, format, args
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][COMMAND]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}

		va_end (args);
	}

	return retval;

}

// checks to see if the key exists
// returns 0 on success, 1 on error
unsigned int credis_exists (const char *key) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"EXISTS %s",
				key
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][EXISTS]: %lld\n", reply->integer
				);
				#endif

				if (reply->integer) {
					retval = 0;
				}

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// sets a key value pair
// returns 0 on success, 1 on error
unsigned int credis_set (
	const char *key, const char *value
) {

	unsigned int retval = 1;

	if (key && value) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"SET %s %s",
				key, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][SET]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// sets a key value pair taking an integer
// returns 0 on success, 1 on error
unsigned int credis_set_int (
	const char *key, const int value
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"SET %s %d",
				key, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][SET]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// sets a key value pair taking an unsigned int
// returns 0 on success, 1 on error
unsigned int credis_set_unsigned (
	const char *key, const unsigned int value
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"SET %s %u",
				key, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][SET]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// sets a key value pair taking a size_t
// returns 0 on success, 1 on error
unsigned int credis_set_large (
	const char *key, const size_t value
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"SET %s %lu",
				key, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][SET]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// sets a key value pair taking a double
// returns 0 on success, 1 on error
unsigned int credis_set_double (
	const char *key, const double value
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"SET %s %f",
				key, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout, "[CREDIS][SET]: %s\n", reply->str
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// increments a value by 1
// returns 0 on success, 1 on error
unsigned int credis_incr (const char *key) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"INCR %s",
				key
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][INCR]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// increments a value by specified amount
// returns 0 on success, 1 on error
unsigned int credis_incr_by (
	const char *key, const unsigned int amount
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"INCRBY %s %u",
				key, amount
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][INCRBY]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// decreases a value by 1
// returns 0 on success, 1 on error
unsigned int credis_decr (const char *key) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"DECR %s",
				key
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][DECR]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// decreases a value by specified amount
// returns 0 on success, 1 on error
unsigned int credis_decr_by (
	const char *key, const unsigned int amount
) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"DECRBY %s %u",
				key, amount
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][DECR]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// inserts a new element on the head (left)
// a new list is created when its is ran against an empty key
// returns 0 on success, 1 on error
unsigned int credis_left_push (
	const char *list, const char *value
) {

	unsigned int retval = 1;

	if (list && value) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LPUSH %s %s",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_left_push () but takes an int
// returns 0 on success, 1 on error
unsigned int credis_left_push_int (
	const char *list, const int value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LPUSH %s %d",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_left_push () but takes an unsigned int
// returns 0 on success, 1 on error
unsigned int credis_left_push_unsigned (
	const char *list, const unsigned int value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LPUSH %s %u",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_left_push () but takes a size_t
// returns 0 on success, 1 on error
unsigned int credis_left_push_large (
	const char *list, const size_t value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LPUSH %s %lu",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_left_push () but takes a double
// returns 0 on success, 1 on error
unsigned int credis_left_push_double (
	const char *list, const double value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LPUSH %s %f",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// inserts a new element on the tail (right)
// a new list is created when its is ran against an empty key
// returns 0 on success, 1 on error
unsigned int credis_right_push (
	const char *list, const char *value
) {

	unsigned int retval = 1;

	if (list && value) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"RPUSH %s %s",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][RPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_right_push () but takes an int
// returns 0 on success, 1 on error
unsigned int credis_right_push_int (
	const char *list, const int value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"RPUSH %s %d",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][RPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_right_push () but takes an unsigned int
// returns 0 on success, 1 on error
unsigned int credis_right_push_unsigned (
	const char *list, const unsigned int value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"RPUSH %s %u",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][RPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_right_push () but takes a size_t
// returns 0 on success, 1 on error
unsigned int credis_right_push_large (
	const char *list, const size_t value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"RPUSH %s %lu",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][RPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// works like credis_right_push () but takes a double
// returns 0 on success, 1 on error
unsigned int credis_right_push_double (
	const char *list, const double value
) {

	unsigned int retval = 1;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"RPUSH %s %f",
				list, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][RPUSH]: %lld\n", reply->integer
				);
				#endif

				freeReplyObject (reply);

				retval = 0;
			}

			credis_client_return (client);
		}
	}

	return retval;

}

// returns the length of the list
long long credis_list_length (
	const char *list
) {

	long long length = 0;

	if (list) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LLEN %s",
				list
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LLEN]: %lld\n", reply->integer
				);
				#endif

				length = reply->integer;

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}
	}

	return length;

}

// removes the first count occurrences of elements
// equal to element from the list stored at key
// count > 0: remove elements equal to element moving from head to tail
// count < 0: remove elements equal to element moving from tail to head
// count = 0: remove all elements equal to element
// returns the number of removed elements
unsigned int credis_list_remove (
	const char *list, const int count, const char *value
) {

	unsigned int result = 0;

	if (list && value) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LREM %s %d %s",
				list, count, value
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][LREM]: %lld\n", reply->integer
				);
				#endif

				result = (unsigned int) (reply->integer < 0) ? 0 : reply->integer;

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}
	}

	return result;

}

// deletes a key value pair
// returns 0 on success, 1 on error
unsigned int credis_del (const char *key) {

	unsigned int retval = 1;

	if (key) {
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"DEL %s",
				key
			);

			if (reply) {
				#ifdef CREDIS_DEBUG
				(void) fprintf (
					stdout,
					"[CREDIS][DEL]: %lld\n", reply->integer
				);
				#endif

				if (reply->integer) {
					retval = 0;
				}

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}
	}

	return retval;

}
