#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <credis/redis.h>
#include <credis/crud.h>

int main (int argc, const char **argv) {

	credis_set_hostname ("127.0.0.1");
	
	if (!credis_init ()) {
		credis_ping_db ();

		credis_set ("oki", "doki");

		credis_end ();
	}

	return 0;

}
