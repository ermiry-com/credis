#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include <credis/crud.h>
#include <credis/redis.h>
#include <credis/version.h>

#include "test.h"

static size_t n_good_censos = 0;

// total amount of photos in each censo
static double min_photos_in_censo_count = __DBL_MAX__;
static double max_photos_in_censo_count = 0;
static double sum_photos_in_censo_counts = 0;
static double average_photos_in_censo_count = 0;

static void set_censos_counts (
	const size_t n_censos,
	const size_t n_bad_user_censos,
	const size_t n_server_error_censos
) {

	(void) credis_command (
		"MSET n_censos %lu n_bad_user_censos %lu n_server_error_censos %lu",
		n_censos, n_bad_user_censos, n_server_error_censos
	);

}

static void fetch_censos_counts (void) {

	CredisClient *client = credis_client_get ();
	if (client) {
		redisReply *reply = (redisReply *) redisCommand (
			client->redis_context,
			"MGET n_censos "
			"n_bad_user_censos "
			"n_server_error_censos"
		);

		if (reply) {
			(void) printf ("Fetched %lu elements!\n", reply->elements);

			for (size_t idx = 0; idx < reply->elements; idx++) {
				(void) printf (
					"[%lu]: %d - %s\n",
					idx, reply->element[idx]->type, reply->element[idx]->str
				);
			}

			freeReplyObject (reply);
		}

		credis_client_return (client);
	}

}

static void delete_censos_counts (void) {

	test_check_unsigned_eq (credis_del ("n_censos"), 0, NULL);
	test_check_unsigned_eq (credis_del ("n_bad_user_censos"), 0, NULL);
	test_check_unsigned_eq (credis_del ("n_server_error_censos"), 0, NULL);

}

static void fetch_photos_in_censo_count (void) {

	CredisClient *client = credis_client_get ();
	if (client) {
		redisReply *reply = (redisReply *) redisCommand (
			client->redis_context,
			"MGET min_photos_in_censo_count max_photos_in_censo_count "
			"sum_photos_in_censo_counts average_photos_in_censo_count"
		);

		if (reply) {
			(void) printf ("Fetched %lu elements!\n", reply->elements);

			for (size_t idx = 0; idx < reply->elements; idx++) {
				(void) printf (
					"[%lu]: %d - %s\n",
					idx, reply->element[idx]->type, reply->element[idx]->str
				);
			}

			(void) printf ("\n");

			freeReplyObject (reply);
		}

		credis_client_return (client);
	}

}

void update_photos_in_censo_count (
	const double censo_total_photos_count
) {

	n_good_censos += 1;

	if (censo_total_photos_count < min_photos_in_censo_count)
		min_photos_in_censo_count = censo_total_photos_count;

	if (censo_total_photos_count > max_photos_in_censo_count)
		max_photos_in_censo_count = censo_total_photos_count;

	sum_photos_in_censo_counts += censo_total_photos_count;
	average_photos_in_censo_count = (
		sum_photos_in_censo_counts / n_good_censos
	);

	(void) credis_command (
		"MSET min_photos_in_censo_count %f max_photos_in_censo_count %f",
		min_photos_in_censo_count,
		max_photos_in_censo_count
	);

	(void) credis_command (
		"MSET sum_photos_in_censo_counts %f average_photos_in_censo_count %f",
		sum_photos_in_censo_counts,
		average_photos_in_censo_count
	);

}

void delete_photos_in_censo_count (void) {

	test_check_unsigned_eq (credis_del ("min_photos_in_censo_count"), 0, NULL);
	test_check_unsigned_eq (credis_del ("max_photos_in_censo_count"), 0, NULL);
	test_check_unsigned_eq (credis_del ("sum_photos_in_censo_counts"), 0, NULL);
	test_check_unsigned_eq (credis_del ("average_photos_in_censo_count"), 0, NULL);

}

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");

	if (!credis_init ()) {
		credis_ping_db ();

		set_censos_counts (1, 2, 3);

		update_photos_in_censo_count (8);
		update_photos_in_censo_count (10);
		update_photos_in_censo_count (6);

		fetch_censos_counts ();

		fetch_photos_in_censo_count ();

		delete_censos_counts ();
		delete_photos_in_censo_count ();

		credis_end ();
	}

	return 0;

}
