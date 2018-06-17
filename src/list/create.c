/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** create a new list
*/

#include <stdlib.h>
#include "aled_list.h"

aled_list_t *aled_list_create(void)
{
	aled_list_t *list;

	if ((list = malloc(sizeof(aled_list_t))) == NULL)
		return (NULL);
	list->back = list->head = NULL;
	list->len = 0;
	return (list);
}
