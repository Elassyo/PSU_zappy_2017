/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player movement routines
*/

#include "zappy_server.h"

void zpy_srv_player_move_forward(zpy_srv_map_t *map, zpy_srv_player_t *player)
{
	switch (player->direction) {
	case UP:
		player->y = (player->y + map->height - 1) % map->height;
		break;
	case DOWN:
		player->y = (player->y + 1) % map->height;
		break;
	case LEFT:
		player->x = (player->x + map->width - 1) % map->width;
		break;
	case RIGHT:
		player->x = (player->x + 1) % map->width;
		break;
	default:
		break;
	}
}

void zpy_srv_player_turn_left(zpy_srv_player_t *player)
{
	player->direction = (player->direction + NDIRECTIONS - 1) % NDIRECTIONS;
}

void zpy_srv_player_turn_right(zpy_srv_player_t *player)
{
	player->direction = (player->direction + 1) % NDIRECTIONS;
}
