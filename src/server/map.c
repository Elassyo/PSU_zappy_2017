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
	unsigned int amt;
	unsigned int x;
	unsigned int y;

	for (zpy_item_type_t res = LINEMATE; res < NITEM_TYPES; res++) {
		amt = server->map.width * server->map.height / 5;
		if (res == THYSTAME)
			amt /= 6;
		for (unsigned int i = 0; i < amt; i++) {
			x = rand() % server->map.width;
			y = rand() % server->map.height;
			zpy_srv_map_add_item(server, x, y, res);
		}
	}
}

void zpy_srv_map_add_food(zpy_srv_t *server)
{
	unsigned int food_amt = server->map.width * server->map.height / 2;
	unsigned int x;
	unsigned int y;

	for (unsigned int i = 0; i < food_amt; i++) {
		x = rand() % server->map.width;
		y = rand() % server->map.height;
		zpy_srv_map_add_item(server, x, y, FOOD);
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
