/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player movement routines
*/

#include "zappy_server.h"

void zpy_srv_player_move(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_direction_t direction)
{
	zpy_srv_client_t *client = player->conn->data;

	switch (direction) {
	case UP:
		player->y = MOD(player->y - 1, map->height);
		break;
	case DOWN:
		player->y = MOD(player->y + 1, map->height);
		break;
	case LEFT:
		player->x = MOD(player->x - 1, map->height);
		break;
	case RIGHT:
		player->x = MOD(player->x + 1, map->height);
		break;
	default:
		break;
	}
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_ppo, player);
}

void zpy_srv_player_turn_left(zpy_srv_player_t *player)
{
	zpy_srv_client_t *client = player->conn->data;

	player->direction = (player->direction + NDIRECTIONS - 1) % NDIRECTIONS;
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_ppo, player);
}

void zpy_srv_player_turn_right(zpy_srv_player_t *player)
{
	zpy_srv_client_t *client = player->conn->data;

	player->direction = (player->direction + 1) % NDIRECTIONS;
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_ppo, player);
}
