#include <stdio.h>

#include "credis/version.h"

// print full erver version information
void credis_version_print_full (void) {

	printf ("\nCredis Version: %s\n", CREDIS_VERSION_NAME);
	printf ("Release Date & time: %s - %s\n", CREDIS_VERSION_DATE, CREDIS_VERSION_TIME);
	printf ("Author: %s\n\n", CREDIS_VERSION_AUTHOR);

}

// print the version id
void credis_version_print_version_id (void) {

	printf ("\nCredis Version ID: %s\n", CREDIS_VERSION);

}

// print the version name
void credis_version_print_version_name (void) {

	printf ("\nCredis Version: %s\n", CREDIS_VERSION_NAME);

}