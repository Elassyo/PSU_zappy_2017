/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** add a new link to a list
*/

#include <stdlib.h>
#include "aled_list.h"

static int aled_list_new_link(aled_list_link_t *pnt, void *data)
{
	aled_list_link_t *new_link;

	if ((new_link = malloc(sizeof(aled_list_link_t))) == NULL)
		return (EXIT_FAILURE);
	new_link->data = data;
	new_link->next = pnt;
	new_link->prev = pnt->prev;
	pnt->prev->next = new_link;
	pnt->prev = new_link;
	return (EXIT_SUCCESS);
}

int aled_list_add(aled_list_t *list, unsigned int index, void *data)
{
	char sign;
	unsigned int i;
	aled_list_link_t *pnt;

	if (index == list->len - 1)
		return (aled_list_push_back(list, data));
	if (index == 0)
		return (aled_list_push(list, data));
	sign = (index <= list->len / 2 ? 1 : -1);
	i = (sign > 0 ? 0 : list->len - 1);
	pnt = (sign > 0 ? list->head : list->back);
	while (i += sign, i - sign != index)
		pnt = (sign > 0 ? pnt->next : pnt->prev);
	list->len++;
	return (aled_list_new_link(pnt, data));
}
