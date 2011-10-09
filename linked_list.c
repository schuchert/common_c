#include "linked_list.h"
#include <stdio.h>

#include "CommonMemory.h"

struct linked_list {
	list_node *head;
};

struct list_node {
	void *data;
	list_node *next;
};

struct list_iterator {
	linked_list *list;
	list_node *current;
};

static void list_node_release_delete(list_node *node, RELEASE_F f) {
	if (NULL != f)
		f(node->data);
	node->data = 0;
	node->next = 0;
	release(node);
}

static list_node *list_node_create(void *value) {
	list_node *node = acquire(sizeof(list_node));
	node->data = value;
	node->next = NULL;
	return node;
}

linked_list *linked_list_create(void) {
	linked_list *l = acquire(sizeof(linked_list));
	l->head = list_node_create(NULL);
	return l;
}

void linked_list_destroy(linked_list *aList) {
	linked_list_release_destroy(aList, NULL);
}

void linked_list_release_destroy(linked_list *aList, RELEASE_F f) {
	if (aList != NULL) {
		list_node *current = aList->head;
		list_node *next = NULL;
		do {
			next = current->next;
			list_node_release_delete(current, f);
			current = next;
		} while(NULL != next);

		release(aList);
	}
}

void* linked_list_find(linked_list *list, COMP_F f, const void *other) {
	list_iterator *iter = linked_list_begin(list);

	while (linked_list_has_next(iter)) {
		void *current = linked_list_next(iter);
		if (f(current, other)) {
			linked_list_end(iter);
			return current;
		}
	}

	linked_list_end(iter);
	return NULL;
}

size_t linked_list_size(linked_list *list) {
	size_t size = 0;
	list_node *current = list->head;
	while (NULL != current->next) {
		++size;
		current = current->next;
	}
	return size;
}

list_node *linked_list_last(linked_list *list) {
	list_node *current = list->head;
	while (NULL != current->next)
		current = current->next;
	return current;
}

void linked_list_add(linked_list *list, void *value) {
	list_node *last = linked_list_last(list);
	last->next = list_node_create(value);
}

list_iterator *linked_list_begin(linked_list *list) {
	list_iterator *iter = acquire(sizeof(list_iterator));
	iter->list = list;
	iter->current = list->head;
	return iter;
}

int linked_list_has_next(list_iterator *iter) {
	return iter->current->next != NULL;
}

void *linked_list_next(list_iterator *iter) {
	iter->current = iter->current->next;
	return list_node_data(iter->current);
}

void linked_list_end(list_iterator *iter) {
	release(iter);
}

void *list_node_data(list_node *node) {
	return node->data;
}
