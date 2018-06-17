/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** player movement routines
*/

#include "server_map.h"

static void player_loop_map(server_map_t *map, player_t *player)
{
	if (player->pos_x == -1)
		player->pos_x = map->width - 1;
	if (player->pos_x == (signed) map->width)
		player->pos_x = 0;
	if (player->pos_y == -1)
		player->pos_y = map->height - 1;
	if (player->pos_y == (signed) map->height)
		player->pos_y = 0;
}

void player_move_forward(server_map_t *map, player_t *player)
{
	switch (player->direction) {
	case UP:
		player->pos_y--;
		break;
	case DOWN:
		player->pos_y++;
		break;
	case LEFT:
		player->pos_x--;
		break;
	case RIGHT:
		player->pos_x++;
		break;
	}
	player_loop_map(map, player);
}

void player_turn_left(player_t *player)
{
	if (player->direction == UP)
		player->direction = LEFT;
	else
		player->direction--;
}

void player_turn_right(player_t *player)
{
	if (player->direction == LEFT)
		player->direction = UP;
	else
		player->direction++;
}
