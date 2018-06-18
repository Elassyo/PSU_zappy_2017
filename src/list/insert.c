/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Insert a node in a list
*/

#include <stdlib.h>

#include "list.h"

int list_insert(list_t *l, unsigned int i, void *data)
{
	list_node_t *node;
	list_node_t *new_node;

	if (i == 0)
		return (list_push(l, data));
	if (i == l->len - 1)
		return (list_push_back(l, data));
	node = list_get_node(l, i);
	if (node == NULL)
		return (1);
	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (1);
	new_node->data = data;
	new_node->prev = node->prev;
	new_node->next = node;
	node->prev->next = new_node;
	node->prev = new_node;
	l->len++;
	return (0);
}
