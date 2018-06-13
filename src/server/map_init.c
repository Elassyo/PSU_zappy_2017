/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** server map init
*/

#include "server_map.h"

server_map_t *server_map_init(size_t width, size_t height)
{
	server_map_t *ret = malloc(sizeof(*ret));

	ret->width = width;
	ret->height = height;
	ret->cells = malloc(sizeof(*ret->cells) * ret->width);
	ret->players = aled_list_create();
	for (size_t i = 0; i < ret->width; i++) {
		ret->cells[i] = malloc(sizeof(*ret->cells) * ret->height);
		for (size_t j = 0; j < ret->height; j++) {
			ret->cells[i][j] = aled_list_create();
		}
	}
	return (ret);
}
