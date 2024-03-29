#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/redis.h>
#include <credis/crud.h>

#include "test.h"

static void credis_test_crud_exists (void) {

	(void) credis_del ("oki");

	test_check_unsigned_eq (credis_exists ("oki"), 1, NULL);

	test_check_unsigned_eq (credis_set ("oki", "doki"), 0, NULL);

	test_check_unsigned_eq (credis_exists ("oki"), 0, NULL);

	test_check_unsigned_eq (credis_del ("oki"), 0, NULL);

}

static void credis_test_crud_set (void) {

	(void) credis_del ("test");

	test_check_unsigned_eq (credis_exists ("test"), 1, NULL);

	test_check_unsigned_eq (credis_set ("test", "hola"), 0, NULL);

	test_check_unsigned_eq (credis_exists ("test"), 0, NULL);

	test_check_unsigned_eq (credis_del ("test"), 0, NULL);

}

static void credis_test_crud_set_int (void) {

	(void) credis_del ("entero");

	test_check_unsigned_eq (credis_exists ("entero"), 1, NULL);

	test_check_unsigned_eq (credis_set_int ("entero", 7), 0, NULL);

	test_check_unsigned_eq (credis_exists ("entero"), 0, NULL);

	test_check_unsigned_eq (credis_del ("entero"), 0, NULL);

}

static void credis_test_crud_set_unsigned (void) {

	(void) credis_del ("unsigned");

	test_check_unsigned_eq (credis_exists ("unsigned"), 1, NULL);

	test_check_unsigned_eq (credis_set_unsigned ("unsigned", 10), 0, NULL);

	test_check_unsigned_eq (credis_exists ("unsigned"), 0, NULL);

	test_check_unsigned_eq (credis_del ("unsigned"), 0, NULL);

}

static void credis_test_crud_set_large (void) {

	(void) credis_del ("largo");

	test_check_unsigned_eq (credis_exists ("largo"), 1, NULL);

	test_check_unsigned_eq (credis_set_large ("largo", 1000000), 0, NULL);

	test_check_unsigned_eq (credis_exists ("largo"), 0, NULL);

	test_check_unsigned_eq (credis_del ("largo"), 0, NULL);

}

static void credis_test_crud_set_double (void) {

	(void) credis_del ("doble");

	test_check_unsigned_eq (credis_exists ("doble"), 1, NULL);

	test_check_unsigned_eq (credis_set_double ("doble", 10.1010), 0, NULL);

	test_check_unsigned_eq (credis_exists ("doble"), 0, NULL);

	test_check_unsigned_eq (credis_del ("doble"), 0, NULL);

}

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		(void) credis_ping_db ();

		credis_test_crud_exists ();

		credis_test_crud_set ();
		credis_test_crud_set_int ();
		credis_test_crud_set_unsigned ();
		credis_test_crud_set_large ();
		credis_test_crud_set_double ();

		credis_end ();
	}

	return 0;

}
