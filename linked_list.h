#pragma once
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct linked_list linked_list;
typedef struct list_node list_node;
typedef struct list_iterator list_iterator;
typedef void (*RELEASE_F)(void *);

linked_list *linked_list_create(void);
void linked_list_destroy(linked_list *aList);
void linked_list_release_destroy(linked_list *aList, RELEASE_F f);
size_t linked_list_size(linked_list *list);
void linked_list_add(linked_list *list, void *value);
list_node *linked_list_last(linked_list *list);

list_iterator *linked_list_begin(linked_list *list);
void linked_list_end(list_iterator *iter);
int linked_list_has_next(list_iterator *iter);
void *linked_list_next(list_iterator *iter);
void *list_node_data(list_node *node);

#ifdef __cplusplus
}
#endif

#endif
