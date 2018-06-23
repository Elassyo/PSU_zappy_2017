/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Get players on tiles
*/

#include "zappy_server.h"

list_t *zpy_srv_map_players_on_tile(zpy_srv_map_t *map,
	unsigned int x, unsigned int y)
{
	list_node_t *node = map->players->head;
	list_t *ret = list_create(false);

	while (node) {
		if (((zpy_srv_player_t*)(node->data))->x == x
				&& ((zpy_srv_player_t*)(node->data))->y == y)
			list_push_back(ret, node->data);
		node = node->next;
	}
	return (ret);
}
