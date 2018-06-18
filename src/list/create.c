/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Create a new list
*/

#include <stdlib.h>

#include "list.h"

list_t *list_create(bool free_on_pop)
{
	list_t *l;

	l = malloc(sizeof(*l));
	if (l == NULL)
		return (NULL);
	l->head = NULL;
	l->back = NULL;
	l->len = 0;
	l->free_on_pop = free_on_pop;
	return (l);
}
