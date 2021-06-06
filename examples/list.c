#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/crud.h>
#include <credis/redis.h>
#include <credis/version.h>

int main (int argc, const char **argv) {

	credis_version_print_full ();

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		credis_ping_db ();

		// push 3 elements to the end of the list
		credis_right_push ("numbers", "one");
		credis_right_push ("numbers", "two");
		credis_right_push ("numbers", "three");

		// push 1 element to the start of the list
		credis_left_push ("numbers", "zero");

		// we expect the result to be:
		// "zero", "one", "two", "three"
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LRANGE numbers 0 -1"
			);

			if (reply) {
				(void) printf ("Elements in numbers (%lu)\n", reply->elements);

				for (size_t idx = 0; idx < reply->elements; idx++) {
					(void) printf ("[%lu]: %s\n", idx, reply->element[idx]->str);
				}

				(void) printf ("\n");

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}

		// remove list
		credis_del ("numbers");

		credis_end ();
	}

	return 0;

}
