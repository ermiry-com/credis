#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/crud.h>
#include <credis/redis.h>
#include <credis/version.h>

#include "test.h"

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		credis_ping_db ();

		(void) credis_del ("numbers");

		// the should not exist
		test_check_unsigned_eq (credis_exists ("numbers"), 1, NULL);

		// push 3 elements to the end of the list
		test_check_unsigned_eq (credis_right_push ("numbers", "one"), 0, NULL);
		test_check_unsigned_eq (credis_right_push ("numbers", "two"), 0, NULL);
		test_check_unsigned_eq (credis_right_push ("numbers", "three"), 0, NULL);

		// the list must be created now
		test_check_unsigned_eq (credis_exists ("numbers"), 0, NULL);

		// push 1 element to the start of the list
		test_check_unsigned_eq (credis_left_push ("numbers", "zero"), 0, NULL);

		// push 2 more elements to the end of the list
		test_check_unsigned_eq (credis_right_push ("numbers", "four"), 0, NULL);
		test_check_unsigned_eq (credis_right_push ("numbers", "five"), 0, NULL);

		// remove one element from each end
		test_check_unsigned_eq (credis_list_remove ("numbers", 1, "zero"), 1, NULL);
		test_check_unsigned_eq (credis_list_remove ("numbers", -1, "five"), 1, NULL);

		// check the length of the list
		test_check_unsigned_eq (credis_list_length ("numbers"), 4, NULL);

		// we expect the result to be:
		// "one", "two", "three", "four"
		CredisClient *client = credis_client_get ();
		if (client) {
			redisReply *reply = (redisReply *) redisCommand (
				client->redis_context,
				"LRANGE numbers 0 -1"
			);

			if (reply) {
				test_check_str_eq (reply->element[0]->str, "one", NULL);
				test_check_str_eq (reply->element[1]->str, "two", NULL);
				test_check_str_eq (reply->element[2]->str, "three", NULL);
				test_check_str_eq (reply->element[3]->str, "four", NULL);

				freeReplyObject (reply);
			}

			credis_client_return (client);
		}

		// remove list
		test_check_unsigned_eq (credis_del ("numbers"), 0, NULL);

		credis_end ();
	}

	return 0;

}
