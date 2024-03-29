# Credis

Credis is a custom wrapper around [hiredis](https://github.com/redis/hiredis) that extends its functionality by implementing a custom clients pool to be used in multi-threaded applications.

## Getting Started

``` c
// set the hostname
// default port 6379 will be used
credis_set_hostname ("127.0.0.1");
	
// initialize credis internal structures
if (!credis_init ()) {
	// test redis connection with a PING command
	credis_ping_db ();

	// sets a key value pair
	credis_set ("oki", "doki");

	// disposes credis internal values
	credis_end ();
}
```

## API Reference

``` c
// returns the current hostname
CREDIS_PUBLIC const char *credis_get_hostname (void);

// sets the hostname
CREDIS_EXPORT void credis_set_hostname (const char *host);

// returns the current configured port
CREDIS_PUBLIC const unsigned int credis_get_port (void);

// sets a custom port to be used
CREDIS_EXPORT void credis_set_port (const unsigned int port);

// sets the connection timeout
// default to 1.5 seconds
CREDIS_EXPORT void credis_set_timeout (
	const long seconds, const long miliseconds
);

// sets the clients pool initial size (default is 16)
CREDIS_EXPORT void credis_set_clients_pool_init (
	const unsigned int clients_pool_init
);

// gets a new client to be used
CREDIS_PUBLIC CredisClient *credis_client_get (void);

// returns a client to the pool after use
CREDIS_PUBLIC void credis_client_return (
	CredisClient *client
);

// initializes credis internal values
CREDIS_EXPORT unsigned int credis_init (void);

// pings the db to test for a success connection
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_ping_db (void);

// sets a key "oki" - value "doki" pair
// to be used for testing
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_test (void);

// checks if the test key "oki" exists
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_exists_test (void);

// removes the test key "oki"
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_remove_test (void);

// disposes credis internal values
CREDIS_EXPORT void credis_end (void);
```

## CRUD

``` c
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

// removes the first count occurrences of elements
// equal to element from the list stored at key
// count > 0: remove elements equal to element moving from head to tail
// count < 0: remove elements equal to element moving from tail to head
// count = 0: remove all elements equal to element
// returns the number of removed elements
CREDIS_EXPORT unsigned int credis_list_remove (
	const char *list, const int count, const char *value
);

// deletes a key value pair
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_del (
	const char *key
);
```
