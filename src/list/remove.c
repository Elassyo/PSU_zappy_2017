/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Remove a node from a list
*/

#include <stdlib.h>

#include "list.h"

int list_remove(list_t *l, unsigned int i)
{
	list_node_t *node;

	if (i == 0)
		return (list_pop(l));
	if (i == l->len - 1)
		return (list_pop_back(l));
	node = list_get_node(l, i);
	if (node == NULL)
		return (1);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	if (l->free_on_pop)
		free(node->data);
	free(node);
	l->len--;
	return (0);
}
