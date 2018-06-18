/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map initialization and destruction
*/

#include <stddef.h>
#include <stdlib.h>

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

void zpy_srv_map_fill(zpy_srv_t *srv)
{
	unsigned int res_amt;
	int x;
	int y;
	zpy_item_type_t resource;

	res_amt = 5 * srv->max_clients + ((rand() % 2 * srv->max_clients) -
		srv->max_clients);
	for (int i = 0; i < res_amt; i++) {
		x = rand() % srv->map.width;
		y = rand() % srv->map.height;
		resource = (zpy_item_type_t) (rand() % (NITEM_TYPES - 1));
		zpy_srv_map_add_item(srv->map, x, y, resource);
		x = rand() % srv->map.width;
		y = rand() % srv->map.height;
		zpy_srv_map_add_item(srv->map, x, y, FOOD);
	}
}