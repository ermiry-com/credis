#ifndef _CREDIS_REDIS_H_
#define _CREDIS_REDIS_H_

#include <time.h>

#include <hiredis/hiredis.h>

#include <credis/collections/pool.h>

#include "credis/client.h"
#include "credis/status.h"

#define REDIS_HOST_SIZE						128

#define REDIS_DEFAULT_PORT					6379

#define REDIS_DEFAULT_TIMEOUT_SECS			1
#define REDIS_DEFAULT_TIMEOUT_MILI			500000

#define REDIS_DEFAULT_CLIENTS_POOL_INIT		16

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Credis {

	unsigned int hostname_len;
	char hostname[REDIS_HOST_SIZE];

	unsigned int port;

	struct timeval timeout;

	unsigned int clients_pool_init;
	CredisPool *clients_pool;

} Credis;

CREDIS_PUBLIC const char *credis_get_hostname (void);

CREDIS_EXPORT void credis_set_hostname (const char *host);

CREDIS_PUBLIC const unsigned int credis_get_port (void);

CREDIS_EXPORT void credis_set_port (const unsigned int port);

// sets the connection timeout
// default to 1.5 seconds
CREDIS_EXPORT void credis_set_timeout (
	const long seconds, const long miliseconds
);

CREDIS_EXPORT void credis_set_clients_pool_init (
	const unsigned int clients_pool_init
);

CREDIS_PUBLIC CredisClient *credis_client_get (void);

CREDIS_PUBLIC void credis_client_return (
	CredisClient *client
);

CREDIS_EXPORT unsigned int credis_init (void);

// pings the db to test for a success connection
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_ping_db (void);

// sets a key "oki" - value "doki" pair
// to be used for testing
// returns 0 on success, 1 on error
CREDIS_EXPORT unsigned int credis_set_test (void);

CREDIS_EXPORT void credis_end (void);

#ifdef __cplusplus
}
#endif

#endif