/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** get an element from a list
*/

#include <stdlib.h>
#include "aled_list.h"

void *aled_list_get(aled_list_t *list, unsigned int index)
{
	char sign;
	unsigned int i;
	aled_list_link_t *pnt;

	if (index >= list->len)
		return (NULL);
	if (index == list->len - 1)
		return (list->back->data);
	if (index == 0)
		return (list->head->data);
	sign = (index <= list->len / 2 ? 1 : -1);
	i = (sign > 0 ? 0 : list->len - 1);
	pnt = (sign > 0 ? list->head : list->back);
	while (i += sign, i - sign != index)
		pnt = (sign > 0 ? pnt->next : pnt->prev);
	return (pnt->data);
}
