/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Get an element from a list
*/

#include <stdlib.h>

#include "list.h"

list_node_t *list_get_node(list_t *l, unsigned int index)
{
	char sign;
	unsigned int i;
	list_node_t *node;

	if (index >= l->len)
		return (NULL);
	if (index == 0)
		return (l->head);
	if (index == l->len - 1)
		return (l->back);
	sign = index <= l->len / 2 ? 1 : -1;
	i = sign > 0 ? 0 : l->len - 1;
	node = sign > 0 ? l->head : l->back;
	while (i != index) {
		node = sign > 0 ? node->next : node->prev;
		i += sign;
	}
	return (node);
}

void *list_get(list_t *l, unsigned int i)
{
	list_node_t *node;

	node = list_get_node(l, i);
	if (node == NULL)
		return (NULL);
	return (node->data);
}
