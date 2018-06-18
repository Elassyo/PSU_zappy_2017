/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Remove the first or last node of a list
*/

#include <stdlib.h>

#include "list.h"

int list_pop(list_t *l)
{
	list_node_t *tmp;

	if (l->len == 0)
		return (1);
	tmp = l->head;
	l->head = tmp->next;
	if (l->head)
		l->head->prev = NULL;
	if (l->free_on_pop)
		free(tmp->data);
	free(tmp);
	l->len--;
	return (0);
}

int list_pop_back(list_t *l)
{
	list_node_t *tmp;

	if (l->len == 0)
		return (1);
	tmp = l->back;
	l->back = tmp->prev;
	if (l->back)
		l->back->next = NULL;
	if (l->free_on_pop)
		free(tmp->data);
	free(tmp);
	l->len--;
	return (0);
}
