#ifndef _CREDIS_VERSION_H_
#define _CREDIS_VERSION_H_

#define CREDIS_VERSION						"1.0"
#define CREDIS_VERSION_NAME					"Release 1.0"
#define CREDIS_VERSION_DATE					"04/12/2020"
#define CREDIS_VERSION_TIME					"19:38 CST"
#define CREDIS_VERSION_AUTHOR				"Erick Salas"

// print full credis version information
extern void credis_version_print_full (void);

// print the version id
extern void credis_version_print_version_id (void);

// print the version name
extern void credis_version_print_version_name (void);

#endif