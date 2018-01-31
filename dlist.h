#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/**
 * Doubly linked list implementation.
 *
 * This is designed to have a C++ esque "templated" feel to them, in that you can just refer
 * to the type as dlist(type) anywhere you need the type to exist. (You can also always use
 * struct dlist_typename as the type, too).
 *
 * This structure consists of a "full list" type that manages element types. All of the raw element
 * type operations are exposed too, if you ever need to deal with them in some manner.
 *
 * The structure itself is declared when dlist_declare is run. 
 */

#define dlist(typename) \
    struct dlist_##typename

#define dlist_element(typename) \
    struct dlist_element_##typename

#define dlist_pop_decl(type, typename) \
type dlist_##typename##_pop( dlist(typename)* list ) { \
    dlist_element(typename) *element = list->tail; \
    list->tail = list->tail->prev; \
    type retval = element->data; \
    dlistel_break(element); \
    free(element); \
    return retval; \
}

#define dlist_unshift_decl(type, typename) \
type dlist_##typename##_unshift( dlist(typename)* list ) { \
    dlist_element(typename) *element = list->head; \
    list->head = list->head->next; \
    dlistel_break(element); \
    type retval = element->data; \
    free(element); \
    return retval; \
}

#define dlist_declare(type, typename) \
    dlist(typename) { \
        dlist_element(typename) *head; \
        dlist_element(typename) *tail; \
    }; \
    dlist_element(typename){ \
        type data; \
        dlist_element(typename) *next; \
        dlist_element(typename) *prev; \
    }; \
    dlist_unshift_decl(type, typename); \
    dlist_pop_decl(type, typename)


// dlist_element() operations

#define dlistel_new(type) calloc(1, sizeof(dlist_element(type)))

#define dlistel_data(item) (item)->data

// Raw link operation
#define dlistel_link(item_a, item_b) do { \
    if (item_a) item_a->next = item_b; \
    if (item_b) item_b->prev = item_a; \
} while (0)

// Raw unlink operation. Unlinks the two items.
#define dlistel_break(a) do { \
    if (!a) break; \
    if (a->next) a->next->prev = a->prev; \
    if (a->prev) a->prev->next = a->next; \
    a->prev = NULL; \
    a->next = NULL; \
} while (0)

// dlist() operations

#define dlist_new(type) \
    calloc(1, sizeof(dlist(type)))

/**
 * Insert item into the front of the list.
 *
 * This accepts a NULL. In that case, it will create the dlist
 * on the heap.
 */
#define dlist_shift(type, list, item) do { \
    if (!list) list = dlist_new(type); \
    dlist_element(type) *node = dlistel_new(type); \
    node->data = item; \
    dlistel_link(node, list->head); \
    list->head = node; \
    if (!list->tail) { \
        list->tail = node; \
    } \
} while (0)

/**
 * Append new item into the back of the list.
 */
#define dlist_push(type, list, item) do { \
    if (!list) list = dlist_new(type); \
    dlist_element(type) *node = dlistel_new(type); \
    node->data = item; \
    dlistel_link(list->tail, node); \
    list->tail = node; \
    if (!list->head) { \
        list->head = node; \
    } \
} while (0)

/**
 * Remove the first item. Remember to free the list item
 * you got back!
 */
#define dlist_unshift(type, list) dlist_##type##_unshift(list)

/**
 * Remove the last item and place it into the variable item
 */
#define dlist_pop(type, list) dlist_##type##_pop(list)

// Free a list, including all the linked items.
#define dlist_free(type, list) do { \
    dlist_element(type) *cursor = list->head, *previous = NULL; \
    while (cursor) { \
        previous = cursor; \
        cursor = cursor->next; \
        free(previous); \
    } \
    free(list); \
} while (0)


/**
 * Syntax sugar to iterate over a dlist.
 */
#define dlist_foreach(type, list, name) \
	dlist_element(type) *name;\
    for (name = list->head; name != NULL; name = name->next)

#define dlist_foreach_rev(type, list, name) \
	dlist_element(type) *name; \
    for (name = list->tail; name != NULL; name = name->prev)

// common dlists; declare more after your data structures
dlist_declare(char*, string);
dlist_declare(char, char);
dlist_declare(int, int);
dlist_declare(float, float);
dlist_declare(double, double);

#endif /* end of include guard: FLIST_H */
