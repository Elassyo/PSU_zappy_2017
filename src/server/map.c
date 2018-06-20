/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map initialization and destruction
*/

#include <stdlib.h>

#include "zappy_server.h"

static void zpy_srv_map_fill(zpy_srv_t *server)
{
	unsigned int res_amt;
	unsigned int x;
	unsigned int y;
	zpy_item_type_t type;

	res_amt = server->teams->len * server->max_players +
		((rand() % 2 * server->max_players) - server->max_players);
	for (unsigned int i = 0; i < res_amt; i++) {
		x = rand() % server->map.width;
		y = rand() % server->map.height;
		type = (zpy_item_type_t) (rand() % (NITEM_TYPES - 1)) + 1;
		zpy_srv_map_add_item(&server->map, x, y, type);
		x = rand() % server->map.width;
		y = rand() % server->map.height;
		zpy_srv_map_add_item(&server->map, x, y, FOOD);
	}
}

bool zpy_srv_map_init(zpy_srv_t *server)
{
	server->map.players = list_create(false);
	server->map.items = list_create(true);
	if (server->map.players == NULL || server->map.items == NULL)
		return (false);
	zpy_srv_map_fill(server);
	return (true);
}

void zpy_srv_map_cleanup(zpy_srv_map_t *map)
{
	list_destroy(map->players);
	list_destroy(map->items);
}
