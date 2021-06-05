#include <stdio.h>

#include "credis/version.h"

// print full credis version information
void credis_version_print_full (void) {

	(void) printf ("\nCredis Version: %s\n", CREDIS_VERSION_NAME);
	(void) printf ("Release Date & time: %s - %s\n", CREDIS_VERSION_DATE, CREDIS_VERSION_TIME);
	(void) printf ("Author: %s\n\n", CREDIS_VERSION_AUTHOR);

}

// print the version id
void credis_version_print_version_id (void) {

	(void) printf ("\nCredis Version ID: %s\n", CREDIS_VERSION);

}

// print the version name
void credis_version_print_version_name (void) {

	(void) printf ("\nCredis Version: %s\n", CREDIS_VERSION_NAME);

}
