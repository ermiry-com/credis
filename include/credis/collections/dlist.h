#ifndef _CREDIS_COLLECTIONS_DLIST_H_
#define _CREDIS_COLLECTIONS_DLIST_H_

#include <stdbool.h>

#include <pthread.h>

#include "credis/config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CredisListElement {

	struct CredisListElement *prev;
	void *data;
	struct CredisListElement *next;

} CredisListElement;

typedef struct CredisList {

	size_t size;

	CredisListElement *start;
	CredisListElement *end;

	void (*destroy)(void *data);
	int (*compare)(const void *one, const void *two);

	pthread_mutex_t *mutex;

} CredisList;

#define credis_dlist_start(list) ((list)->start)
#define credis_dlist_end(list) ((list)->end)

#define credis_dlist_element_data(element) ((element)->data)
#define credis_dlist_element_next(element) ((element)->next)

#define credis_dlist_for_each(dlist, le)					\
	for (le = dlist->start; le; le = le->next)

#define credis_dlist_for_each_backwards(dlist, le)			\
	for (le = dlist->end; le; le = le->prev)

// sets a list compare function
// compare must return -1 if one < two, must return 0 if they are equal, and must return 1 if one > two
extern void credis_dlist_set_compare (
	CredisList *list,
	int (*compare)(const void *one, const void *two)
);

// sets list destroy function
extern void credis_dlist_set_destroy (
	CredisList *list,
	void (*destroy)(void *data)
);

// thread safe method to get the dlist's size
extern size_t credis_dlist_size (const CredisList *dlist);

extern bool credis_dlist_is_empty (const CredisList *dlist);

extern bool credis_dlist_is_not_empty (const CredisList *dlist);

extern void credis_dlist_delete (void *credis_dlist_ptr);

extern CredisList *credis_dlist_init (
	void (*destroy)(void *data),
	int (*compare)(const void *one, const void *two)
);

extern void credis_dlist_reset (CredisList *dlist);

extern void credis_dlist_clear (void *credis_dlist_ptr);

/*** insert ***/

extern unsigned int credis_dlist_insert_after (
	CredisList *dlist,
	CredisListElement *element, const void *data
);

/*** remove ***/

// removes the dlist element from the dlist and returns the data
// NULL for the start of the list
extern void *credis_dlist_remove_element (
	CredisList *dlist, CredisListElement *element
);

#ifdef __cplusplus
}
#endif

#endif