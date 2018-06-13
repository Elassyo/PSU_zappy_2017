/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** delete whole list
*/

#include <stdlib.h>
#include "aled_list.h"

void aled_list_destroy(aled_list_t *list)
{
	while (list->len > 0 && list->head != NULL && list->back != NULL)
		aled_list_pop(list);
	free(list);
}
