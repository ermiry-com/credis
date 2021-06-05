#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>

#include "credis/collections/dlist.h"

static inline void list_element_delete (CredisListElement *le);

#pragma region internal

static CredisListElement *list_element_new (void) {

	CredisListElement *le = (CredisListElement *) malloc (sizeof (CredisListElement));
	if (le) {
		le->next = le->prev = NULL;
		le->data = NULL;
	}

	return le;

}

static inline void list_element_delete (CredisListElement *le) { if (le) free (le); }

static CredisList *credis_dlist_new (void) {

	CredisList *dlist = (CredisList *) malloc (sizeof (CredisList));
	if (dlist) {
		dlist->size = 0;
		dlist->start = NULL;
		dlist->end = NULL;
		dlist->destroy = NULL;
		dlist->compare = NULL;

		dlist->mutex = NULL;
	}

	return dlist;

}

static void credis_dlist_internal_insert_after_actual (
	CredisList *dlist, CredisListElement *element, CredisListElement *le
) {

	if (element == NULL) {
		if (dlist->size == 0) dlist->end = le;
		else dlist->start->prev = le;

		le->next = dlist->start;
		le->prev = NULL;
		dlist->start = le;
	}

	else {
		if (element->next == NULL) dlist->end = le;

		le->next = element->next;
		le->prev = element;
		element->next = le;
	}

}

static unsigned int credis_dlist_internal_insert_after (
	CredisList *dlist, CredisListElement *element, const void *data
) {

	unsigned int retval = 1;

	CredisListElement *le = list_element_new ();
	if (le) {
		le->data = (void *) data;

		credis_dlist_internal_insert_after_actual (
			dlist, element, le
		);

		dlist->size++;

		retval = 0;
	}

	return retval;

}

static CredisListElement *credis_dlist_internal_remove_element_actual (
	CredisList *dlist, CredisListElement *element, void **data
) {

	CredisListElement *old = NULL;

	if (element == NULL) {
		*data = dlist->start->data;
		old = dlist->start;
		dlist->start = dlist->start->next;
		if (dlist->start != NULL) dlist->start->prev = NULL;
	}

	else {
		*data = element->data;
		old = element;

		CredisListElement *prevElement = element->prev;
		CredisListElement *nextElement = element->next;

		if (prevElement != NULL && nextElement != NULL) {
			prevElement->next = nextElement;
			nextElement->prev = prevElement;
		}

		else {
			// we are at the start of the dlist
			if (prevElement == NULL) {
				if (nextElement != NULL) nextElement->prev = NULL;
				dlist->start = nextElement;
			}

			// we are at the end of the dlist
			if (nextElement == NULL) {
				if (prevElement != NULL) prevElement->next = NULL;
				dlist->end = prevElement;
			}
		}
	}

	return old;

}

static void *credis_dlist_internal_remove_element (
	CredisList *dlist, CredisListElement *element
) {

	void *data = NULL;
	if (dlist->size > 0) {
		list_element_delete (
			credis_dlist_internal_remove_element_actual (
				dlist, element, &data
			)
		);

		dlist->size--;

		if (dlist->size == 0) {
			dlist->start = NULL;
			dlist->end = NULL;
		}
	}

	return data;

}

static void credis_dlist_internal_remove_elements (
	CredisList *dlist
) {

	void *data = NULL;
	while (dlist->size > 0) {
		data = credis_dlist_internal_remove_element (dlist, NULL);
		if (data) {
			if (dlist->destroy) dlist->destroy (data);
		}
	}

}

static void credis_dlist_internal_delete (
	CredisList *dlist
) {

	credis_dlist_internal_remove_elements (dlist);

	(void) pthread_mutex_unlock (dlist->mutex);
	(void) pthread_mutex_destroy (dlist->mutex);
	free (dlist->mutex);

	free (dlist);

}

#pragma endregion

void credis_dlist_set_compare (
	CredisList *dlist, int (*compare)(const void *one, const void *two)
) {

	if (dlist) dlist->compare = compare;

}

void credis_dlist_set_destroy (
	CredisList *dlist, void (*destroy)(void *data)
) {

	if (dlist) dlist->destroy = destroy;

}

size_t credis_dlist_size (const CredisList *dlist) {

	size_t retval = 0;

	if (dlist) {
		(void) pthread_mutex_lock (dlist->mutex);

		retval = dlist->size;

		(void) pthread_mutex_unlock (dlist->mutex);
	}

	return retval;

}

bool credis_dlist_is_empty (const CredisList *dlist) {

	bool retval = true;

	if (dlist) {
		(void) pthread_mutex_lock (dlist->mutex);

		retval = (dlist->size == 0);

		(void) pthread_mutex_unlock (dlist->mutex);
	}

	return retval;

}

bool credis_dlist_is_not_empty (const CredisList *dlist) {

	bool retval = false;

	if (dlist) {
		(void) pthread_mutex_lock (dlist->mutex);

		retval = (dlist->size > 0);

		(void) pthread_mutex_unlock (dlist->mutex);
	}

	return retval;

}

void credis_dlist_delete (void *credis_dlist_ptr) {

	if (credis_dlist_ptr) {
		CredisList *dlist = (CredisList *) credis_dlist_ptr;

		(void) pthread_mutex_lock (dlist->mutex);

		credis_dlist_internal_delete (dlist);
	}

}

CredisList *credis_dlist_init (
	void (*destroy)(void *data),
	int (*compare)(const void *one, const void *two)
) {

	CredisList *dlist = credis_dlist_new ();

	if (dlist) {
		dlist->destroy = destroy;
		dlist->compare = compare;

		dlist->mutex = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
		pthread_mutex_init (dlist->mutex, NULL);
	}

	return dlist;

}

// destroys all of the dlist's elements and their data but keeps the dlist
void credis_dlist_reset (CredisList *dlist) {

	if (dlist) {
		(void) pthread_mutex_lock (dlist->mutex);

		if (dlist->size > 0) {
			void *data = NULL;
			while (dlist->size > 0) {
				data = credis_dlist_internal_remove_element (dlist, NULL);
				if (data != NULL && dlist->destroy != NULL) dlist->destroy (data);
			}
		}

		dlist->start = NULL;
		dlist->end = NULL;
		dlist->size = 0;

		(void) pthread_mutex_unlock (dlist->mutex);
	}

}

// only gets rid of the list elements, but the data is kept
// this is usefull if another dlist or structure points to the same data
void credis_dlist_clear (void *credis_dlist_ptr) {

	if (credis_dlist_ptr) {
		CredisList *dlist = (CredisList *) credis_dlist_ptr;

		(void) pthread_mutex_lock (dlist->mutex);

		while (dlist->size > 0)
			(void) credis_dlist_internal_remove_element (dlist, NULL);

		(void) pthread_mutex_unlock (dlist->mutex);
	}

}

/*** insert ***/

unsigned int credis_dlist_insert_after (
	CredisList *dlist,
	CredisListElement *element, const void *data
) {

	unsigned int retval = 1;

	if (dlist && data) {
		(void) pthread_mutex_lock (dlist->mutex);

		retval = credis_dlist_internal_insert_after (
			dlist, element, data
		);

		(void) pthread_mutex_unlock (dlist->mutex);
	}

	return retval;

}

/*** remove ***/

void *credis_dlist_remove_element (
	CredisList *dlist, CredisListElement *element
) {

	void *data = NULL;

	if (dlist) {
		(void) pthread_mutex_lock (dlist->mutex);

		data = credis_dlist_internal_remove_element (dlist, element);

		(void) pthread_mutex_unlock (dlist->mutex);
	}

	return data;

}
