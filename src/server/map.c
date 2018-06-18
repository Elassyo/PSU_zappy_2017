/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map initialization and destruction
*/

#include <stddef.h>

#include "zappy_server.h"

bool zpy_srv_map_init(zpy_srv_map_t *map)
{
	map->players = list_create(false);
	map->items = list_create(true);
	if (map->players == NULL || map->items == NULL)
		return (false);
	return (true);
}

void zpy_srv_map_cleanup(zpy_srv_map_t *map)
{
	list_destroy(map->players);
	list_destroy(map->items);
}
