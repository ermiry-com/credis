#ifndef _CREDIS_CRUD_H_
#define _CREDIS_CRUD_H_

#include <stddef.h>

#include "credis/config.h"

#ifdef __cplusplus
extern "C" {
#endif

// issues a command to Redis
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_command (
	const char *format, ...
);

// checks to see if the key exists
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_exists (
	const char *key
);

// sets a key value pair
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set (
	const char *key, const char *value
);

// sets a key value pair taking an integer
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_int (
	const char *key, const int value
);

// sets a key value pair taking an unsigned int
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_unsigned (
	const char *key, const unsigned int value
);

// sets a key value pair taking a size_t
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_large (
	const char *key, const size_t value
);

// sets a key value pair taking a double
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_double (
	const char *key, const double value
);

// increments a value by 1
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_incr (
	const char *key
);

// increments a value by specified amount
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_incr_by (
	const char *key, const unsigned int amount
);

// decreases a value by 1
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_decr (
	const char *key
);

// decreases a value by specified amount
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_decr_by (
	const char *key, const unsigned int amount
);

// inserts a new element on the head (left)
// a new list is created when its is ran against an empty key
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_left_push (
	const char *list, const char *value
);

// works like credis_left_push () but takes an int
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_left_push_int (
	const char *list, const int value
);

// works like credis_left_push () but takes an unsigned int
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_left_push_unsigned (
	const char *list, const unsigned int value
);

// works like credis_left_push () but takes a size_t
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_left_push_large (
	const char *list, const size_t value
);

// works like credis_left_push () but takes a double
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_left_push_double (
	const char *list, const double value
);

// inserts a new element on the tail (right)
// a new list is created when its is ran against an empty key
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_right_push (
	const char *list, const char *value
);

// works like credis_right_push () but takes an int
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_right_push_int (
	const char *list, const int value
);

// works like credis_right_push () but takes an unsigned int
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_right_push_unsigned (
	const char *list, const unsigned int value
);

// works like credis_right_push () but takes a size_t
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_right_push_large (
	const char *list, const size_t value
);

// works like credis_right_push () but takes a double
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_right_push_double (
	const char *list, const double value
);

// returns the length of the list
CREDIS_EXPORT long long credis_list_length (
	const char *list
);

// deletes a key value pair
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_del (
	const char *key
);

#ifdef __cplusplus
}
#endif

#endif