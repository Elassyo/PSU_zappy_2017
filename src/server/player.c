/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Add and remove players from the map
*/

#include <stdlib.h>

#include "zappy_server.h"

zpy_srv_player_t *zpy_srv_player_new(zpy_srv_map_t *map, unsigned short team)
{
	zpy_srv_player_t *player;

	player = malloc(sizeof(*player));
	if (player == NULL)
		return (NULL);
	player->team = team;
	player->x = rand() % map->width;
	player->y = rand() % map->height;
	player->direction = rand() % NDIRECTIONS;
	player->inventory[FOOD] = 1;
	for (int i = 1; i < NITEM_TYPES; i++)
		player->inventory[i] = 0;
	player->level = 1;
	player->food_countdown = 1260;
	list_push_back(map->players, player);
	return (player);
}

void zpy_srv_player_remove(zpy_srv_map_t *map, zpy_srv_player_t *player)
{
	unsigned int i = 0;
	list_node_t *node;

	node = map->players->head;
	while (node != NULL && node->data != player) {
		node = node->next;
		i++;
	}
	if (node == NULL)
		return;
	list_remove(map->players, i);
}

bool zpy_srv_player_tick(zpy_srv_player_t *player)
{
	if (--player->food_countdown == 0) {
		if (player->inventory[FOOD]-- == 0)
			return (false);
		player->food_countdown = 126;
	}
	return (true);
}
