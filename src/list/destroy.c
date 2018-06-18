/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Destroy a list
*/

#include <stdlib.h>

#include "list.h"

void list_destroy(list_t *l)
{
	if (l == NULL)
		return;
	while (l->len > 0 && l->head != NULL && l->back != NULL)
		list_pop(l);
	free(l);
}
