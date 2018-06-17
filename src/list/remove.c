/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** remove link from list
*/

#include <stdlib.h>
#include "aled_list.h"

int aled_list_remove(aled_list_t *list, unsigned int index)
{
	char sign;
	unsigned int i;
	aled_list_link_t *pnt;

	if (index == list->len - 1)
		return (aled_list_pop_back(list), EXIT_SUCCESS);
	if (index == 0)
		return (aled_list_pop(list), EXIT_SUCCESS);
	sign = (index <= list->len / 2 ? 1 : -1);
	i = (sign > 0 ? 0 : list->len - 1);
	pnt = (sign > 0 ? list->head : list->back);
	while (i += sign, i - sign != index)
		pnt = (sign > 0 ? pnt->next : pnt->prev);
	pnt->prev->next = pnt->next;
	pnt->next->prev = pnt->prev;
	free(pnt->data);
	free(pnt);
	list->len--;
	return (EXIT_SUCCESS);
}
