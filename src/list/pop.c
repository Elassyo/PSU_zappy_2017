/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** remove first/last link
*/

#include <stdlib.h>
#include "aled_list.h"

void aled_list_pop(aled_list_t *list)
{
	aled_list_link_t *tmp;

	tmp = list->head;
	list->head = tmp->next;
	if (list->head)
		list->head->prev = NULL;
	free(tmp->data);
	free(tmp);
	list->len--;
}

void aled_list_pop_back(aled_list_t *list)
{
	aled_list_link_t *tmp;

	tmp = list->back;
	list->back = tmp->prev;
	if (list->back)
		list->back->next = NULL;
	free(tmp->data);
	free(tmp);
	list->len--;
}
