#include <stdlib.h>
#include <stdbool.h>

#include "credis/collections/dlist.h"
#include "credis/collections/pool.h"

static CredisPool *credis_pool_new (void) {

	CredisPool *pool = (CredisPool *) malloc (sizeof (CredisPool));
	if (pool) {
		pool->dlist = NULL;

		pool->destroy = NULL;
		pool->create = NULL;

		pool->produce = false;
	}

	return pool;

}

void credis_pool_set_destroy (
	CredisPool *pool, void (*destroy)(void *data)
) {

	if (pool) pool->destroy = destroy;

}

void credis_pool_set_create (
	CredisPool *pool, void *(*create)(void)
) {

	if (pool) pool->create = create;

}

void credis_pool_set_produce_if_empty (
	CredisPool *pool, bool produce
) {

	if (pool) pool->produce = produce;

}

// returns how many elements are inside the pool
size_t credis_pool_size (CredisPool *pool) {

	return pool ? credis_dlist_size (pool->dlist) : 0;

}

CredisPool *credis_pool_create (
	void (*destroy)(void *data)
) {

	CredisPool *pool = credis_pool_new ();
	if (pool) {
		pool->dlist = credis_dlist_init (destroy, NULL);
		pool->destroy = destroy;
	}

	return pool;

}

// uses the create method to populate the pool with n elements (NULL to use pool's set method)
// returns 0 on no error, 1 if at least one element failed to be inserted
unsigned int credis_pool_init (
	CredisPool *pool,
	void *(*create)(void), unsigned int n_elements
) {

	unsigned int retval = 1;

	if (pool) {
		void *(*produce)(void) = create ? create : pool->create;
		if (produce) {
			unsigned int errors = 0;

			for (unsigned int i = 0; i < n_elements; i++) {
				errors |= credis_dlist_insert_after (
					pool->dlist,
					credis_dlist_end (pool->dlist),
					produce ()
				);
			}

			retval = errors;
		}
	}

	return retval;

}

unsigned int credis_pool_push (CredisPool *pool, void *data) {

	unsigned int retval = 1;

	if (pool && data) {
		retval = credis_dlist_insert_after (
			pool->dlist,
			credis_dlist_end (pool->dlist),
			data
		);
	}

	return retval;

}

void *credis_pool_pop (CredisPool *pool) {

	void *retval = NULL;

	if (pool) {
		retval = credis_dlist_remove_element (
			pool->dlist,
			NULL
		);

		if (!retval && pool->produce) {
			retval = pool->create ();
		}
	}

	return retval;

}

void credis_pool_clear (CredisPool *pool) {

	if (pool) {
		credis_dlist_clear (pool->dlist);
	}

}

void credis_pool_reset (CredisPool *pool) {

	if (pool) {
		credis_dlist_reset (pool->dlist);
	}

}

void credis_pool_delete (CredisPool *pool) {

	if (pool) {
		credis_dlist_delete (pool->dlist);

		free (pool);
	}

}
