/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Find element in a list
*/

#include <stddef.h>

#include "list.h"

static bool ptr_cmp(void *a, void *b)
{
	return (a == b);
}

int list_find(list_t *l, void *data, bool (*cmp)(void*, void*))
{
	unsigned int i = 0;
	list_node_t *node;

	node = l->head;
	if (cmp == NULL)
		cmp = &ptr_cmp;
	while (node != NULL && !cmp(node->data, data)) {
		node = node->next;
		i++;
	}
	return (node == NULL ? -1 : (int)i);
}
