#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <inttypes.h>
#include <stddef.h>

typedef struct {
    size_t len;
    size_t capacity;
    size_t item_size;
    void *items;
} array_list;

array_list *array_list_create(size_t item_size, size_t initial_capacity);
size_t array_list_append(array_list *list, void *item);
void array_list_set(array_list *list, void *item, size_t index);
void *array_list_get(array_list *list, size_t index);
void array_list_remove(array_list *list, size_t index);
void array_list_reset(array_list *list);

#endif // ARRAY_LIST_H_
