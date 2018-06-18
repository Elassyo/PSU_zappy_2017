/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Add a node to the front or back of a list
*/

#include <stdlib.h>

#include "list.h"

int list_push(list_t *l, void *data)
{
	list_node_t *node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (1);
	node->data = data;
	node->next = l->head;
	node->prev = NULL;
	if (l->head != NULL)
		l->head->prev = node;
	if (l->back == NULL)
		l->back = node;
	l->head = node;
	l->len++;
	return (0);
}

int list_push_back(list_t *l, void *data)
{
	list_node_t *node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (1);
	node->data = data;
	node->next = NULL;
	node->prev = l->back;
	if (l->back != NULL)
		l->back->next = node;
	if (l->head == NULL)
		l->head = node;
	l->back = node;
	l->len++;
	return (0);
}
