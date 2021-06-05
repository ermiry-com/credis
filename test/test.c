#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/redis.h>
#include <credis/crud.h>

#include "test.h"

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		(void) credis_ping_db ();

		// delete key if it already exists
		(void) credis_del ("oki");

		test_check_unsigned_eq (credis_set_test (), 0, NULL);

		credis_end ();
	}

	return 0;

}
