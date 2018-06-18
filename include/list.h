/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Double linked lists
*/

#if !defined(LIST_H_)
	#define LIST_H_

	#include <stdbool.h>

typedef struct list_node {
	struct list_node *next;
	struct list_node *prev;
	void *data;
} list_node_t;

typedef struct list {
	list_node_t *head;
	list_node_t *back;
	unsigned int len;
	bool free_on_pop;
} list_t;

list_t *list_create(bool free_on_pop);
void list_destroy(list_t *l);
list_node_t *list_get_node(list_t *l, unsigned int index);
void *list_get(list_t *l, unsigned int i);
int list_find(list_t *l, void *data, bool (*cmd)(void*, void*));
bool list_push(list_t *l, void *data);
bool list_push_back(list_t *l, void *data);
bool list_insert(list_t *l, unsigned int i, void *data);
bool list_pop(list_t *l);
bool list_pop_back(list_t *l);
bool list_remove(list_t *l, unsigned int i);

#endif /* !defined (LIST_H_) */
