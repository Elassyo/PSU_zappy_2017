/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** output list to stdout
*/

#include <stdio.h>
#include "aled_list.h"

void aled_list_print_strs(aled_list_t *list, char *format)
{
	unsigned int i;

	i = 0;
	while (i < list->len) {
		printf(format, (char *) aled_list_get(list, i));
		i++;
	}
}
