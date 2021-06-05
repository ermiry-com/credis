#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/redis.h>
#include <credis/crud.h>

#include "test.h"

static void credis_test_crud_exists (void) {

	test_check_unsigned_eq (credis_exists ("oki"), 1, NULL);

	test_check_unsigned_eq (credis_set ("oki", "doki"), 0, NULL);

	test_check_unsigned_eq (credis_exists ("oki"), 0, NULL);

}

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		(void) credis_ping_db ();

		credis_test_crud_exists ();

		credis_end ();
	}

	return 0;

}
