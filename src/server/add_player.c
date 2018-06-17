/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** add new player to map
*/

#include "server_map.h"

void server_map_add_player(server_map_t *map, size_t team)
{
	player_t *player = calloc(1, sizeof(*player));

	player->team = team;
	player->pos_x = rand() % map->width;
	player->pos_y = rand() % map->height;
	player->direction = UP;
	player->level = 1;
	player->food_amount = 1;
	player->food_countdown = 126;
	player->action_countdown = 0;
	aled_list_push_back(map->players, player);
}
