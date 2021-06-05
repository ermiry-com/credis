#ifndef _CREDIS_VERSION_H_
#define _CREDIS_VERSION_H_

#define CREDIS_VERSION				"0.2"
#define CREDIS_VERSION_NAME			"Version 0.2"
#define CREDIS_VERSION_DATE			"05/06/2021"
#define CREDIS_VERSION_TIME			"06:20 CST"
#define CREDIS_VERSION_AUTHOR		"Erick Salas"

#ifdef __cplusplus
extern "C" {
#endif

// print full credis version information
extern void credis_version_print_full (void);

// print the version id
extern void credis_version_print_version_id (void);

// print the version name
extern void credis_version_print_version_name (void);

#ifdef __cplusplus
}
#endif

#endif