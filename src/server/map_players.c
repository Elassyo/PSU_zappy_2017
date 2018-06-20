/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** get players on tiles
*/

#include "zappy_server.h"

list_t *zpy_srv_map_players_on_tile(zpy_srv_map_t *map, size_t x, size_t y)
{
	list_node_t *it = map->players->head;
	list_t *ret = list_create(false);

	while (it) {
		if (((zpy_srv_player_t*)(it->data))->x == x
				&& ((zpy_srv_player_t*)(it->data))->y == y)
			list_push_back(ret, it->data);
		it = it->next;
	}
	return (ret);
}
