#ifndef _CREDIS_CLIENT_H_
#define _CREDIS_CLIENT_H_

#include <hiredis/hiredis.h>

#include "credis/config.h"
#include "credis/status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CredisClient {

	RedisStatus status;

	redisOptions redis_options;
	redisContext *redis_context;

} CredisClient;

// creates and connects a new credis client
CREDIS_PRIVATE void *credis_client_create (void);

CREDIS_PRIVATE void redis_client_destroy (void *client_ptr);

#ifdef __cplusplus
}
#endif

#endif