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
	zpy_srv_player_t *player;
	list_t *ret = list_create(false);

	for (list_node_t *node = map->players->head; node; node = node->next) {
		player = node->data;
		if (player->x && player->y == y)
			list_push_back(ret, player);
	}
	return (ret);
}
