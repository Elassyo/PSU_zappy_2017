/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** add link to front/back of list
*/

#include <stdlib.h>
#include "aled_list.h"

int aled_list_push(aled_list_t *list, void *data)
{
	aled_list_link_t *new_link;

	if ((new_link = malloc(sizeof(aled_list_link_t))) == NULL)
		return (EXIT_FAILURE);
	new_link->data = data;
	new_link->next = list->head;
	new_link->prev = NULL;
	if (list->head)
		list->head->prev = new_link;
	if (!list->back)
		list->back = new_link;
	list->head = new_link;
	list->len++;
	return (EXIT_SUCCESS);
}

int aled_list_push_back(aled_list_t *list, void *data)
{
	aled_list_link_t *new_link;

	if ((new_link = malloc(sizeof(aled_list_link_t))) == NULL)
		return (EXIT_FAILURE);
	new_link->data = data;
	new_link->next = NULL;
	new_link->prev = list->back;
	if (list->back)
		list->back->next = new_link;
	if (!list->head)
		list->head = new_link;
	list->back = new_link;
	list->len++;
	return (EXIT_SUCCESS);
}
