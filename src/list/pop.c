/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Remove the first or last node of a list
*/

#include <stdlib.h>

#include "list.h"

bool list_pop(list_t *l)
{
	list_node_t *tmp;

	tmp = l->head;
	if (tmp == NULL)
		return (false);
	l->head = tmp->next;
	if (l->head != NULL)
		l->head->prev = NULL;
	if (l->back == tmp)
		l->back = NULL;
	if (l->free_on_pop)
		free(tmp->data);
	free(tmp);
	l->len--;
	return (true);
}

bool list_pop_back(list_t *l)
{
	list_node_t *tmp;

	tmp = l->back;
	if (tmp == NULL)
		return (false);
	l->back = tmp->prev;
	if (l->back)
		l->back->next = NULL;
	if (l->head == tmp)
		l->head = NULL;
	if (l->free_on_pop)
		free(tmp->data);
	free(tmp);
	l->len--;
	return (true);
}
