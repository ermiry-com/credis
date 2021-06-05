#ifndef _CREDIS_COLLECTIONS_POOL_H_
#define _CREDIS_COLLECTIONS_POOL_H_

#include <stdlib.h>
#include <stdbool.h>

#include "credis/collections/dlist.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CredisPool {

	CredisList *dlist;

	void (*destroy)(void *data);
	void *(*create)(void);

	bool produce;

} CredisPool;

// sets a destroy method to be used by the pool
// to correctly dispose data
extern void credis_pool_set_destroy (
	CredisPool *pool, void (*destroy)(void *data)
);

// sets a create method to be used by the pool
// to correctly allocate new data
extern void credis_pool_set_create (
	CredisPool *pool, void *(*create)(void)
);

// sets the pool's ability to produce a element
// when a pop request is done and the pool is empty
// the pool will use its create method to allocate
// a new element and fullfil the request
extern void credis_pool_set_produce_if_empty (
	CredisPool *pool, bool produce
);

// returns how many elements are inside the pool
extern size_t credis_pool_size (CredisPool *pool);

// creates a new pool
extern CredisPool *credis_pool_create (
	void (*destroy)(void *data)
);

// uses the create method to populate the pool
// with n elements (NULL to use pool's set method)
// returns 0 on success
// returns 1 if at least one element failed to be inserted
extern unsigned int credis_pool_init (
	CredisPool *pool,
	void *(*create)(void), unsigned int n_elements
);

// inserts the new data at the end of the pool
// returns 0 on success, 1 on error
extern unsigned int credis_pool_push (
	CredisPool *pool, void *data
);

// returns the data that is first in the pool
extern void *credis_pool_pop (CredisPool *pool);

// only gets rid of the pool's elements, but the data is kept
// this is usefull if another structure points to the same data
extern void credis_pool_clear (CredisPool *pool);

// destroys all of the pool's elements and their data
// but keeps the pool
extern void credis_pool_reset (CredisPool *pool);

// deletes the pool and all of its members using
// the destroy method
extern void credis_pool_delete (CredisPool *pool);

#ifdef __cplusplus
}
#endif

#endif