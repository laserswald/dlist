#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/**
 * Doubly linked list implementation.
 *
 * This is designed to have a C++ esque "templated" feel to them, in that you can just refer
 * to the type as dlist(type) anywhere you need the type to exist. (You can also always use
 * struct dlist_typename as the type, too)
 *
 * The structure itself is generated when dlist_declare is run. The dlist name
 */

#define dlist(typename) \
    struct dlist_##typename

#define dlist_declare(type, typename) \
    dlist(typename){                  \
        type data;                    \
        dlist(typename) *next;        \
        dlist(typename) *prev;        \
    }

// common dlists; declare more after your data structures
dlist_declare(char*, string);
dlist_declare(char, char);
dlist_declare(int, int);
dlist_declare(float, float);
dlist_declare(double, double);

#define dlist_new(type) calloc(1, sizeof(dlist(type)))

#define dlist_link(item_a, item_b) do {item_a->next = item_b; item_b->prev = item_a;} while (0)

#define dlist_unlink(a) do {           \
    if (!a) break;                     \
    if (a->next) a->next->prev = NULL; \
    if (a->prev) a->prev->next = NULL; \
    a->prev = NULL;                    \
    a->next = NULL;                    \
} while (0)

/**
 * Syntax sugar to iterate over a dlist.
 */
#define dlist_foreach(list, item) \
    for (item = list; item != NULL; item = item->next)

/**
 * Append new item into the list.
 */
#define dlist_append(type, list, item) do { \
    dlist(type) *node = dlist_new(type);    \
    node->data = item;                      \
    if (!list) {                            \
        list = node;                        \
        break;                              \
    }                                       \
    dlist(type) *cursor = list;             \
    while (cursor->next != NULL)            \
        cursor = cursor->next;              \
    dlist_link(cursor, node);               \
} while (0)


#define dlist_free(type, list) do {               \
    dlist(type) *cursor = list, *previous = NULL; \
    while (cursor) {                              \
        previous = cursor;                        \
        cursor = cursor->next;                    \
        free(previous);                           \
    }                                             \
} while (0)


#endif /* end of include guard: FLIST_H */
