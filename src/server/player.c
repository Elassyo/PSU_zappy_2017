/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Add and remove players from the map
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_player_new(zpy_srv_t *server, unsigned short team)
{
	zpy_srv_player_t *player;

	player = malloc(sizeof(*player));
	if (player == NULL)
		return (false);
	player->cmd_queue = list_create(true);
	if (player->cmd_queue == NULL)
		return (false);
	player->team = team;
	player->x = rand() % server->map.width;
	player->y = rand() % server->map.height;
	player->direction = rand() % NDIRECTIONS;
	memset(player->inventory, 0, sizeof(player->inventory));
	player->inventory[FOOD] = 1;
	player->level = 1;
	player->food_countdown = 1260;
	list_push_back(((zpy_srv_team_t*)list_get(server->teams, team))->
		players, player);
	list_push_back(server->map.players, player);
	return (true);
}

void zpy_srv_player_remove(zpy_srv_t *server, zpy_srv_player_t *player)
{
	zpy_srv_team_t *team;

	list_destroy(player->cmd_queue);
	list_remove(server->map.players,
		list_find(server->map.players, player, NULL));
	team = list_get(server->teams, player->team);
	list_remove(team->players,
		list_find(team->players, player, NULL));
}

bool zpy_srv_player_tick(tcp_conn_t *conn, zpy_srv_player_t *player)
{
	zpy_srv_cmd_t *cmd;

	if (--player->food_countdown == 0) {
		if (player->inventory[FOOD]-- == 0)
			return (false);
		player->food_countdown = 126;
	}
	cmd = list_get(player->cmd_queue, 0);
	if (cmd != NULL && --cmd->countdown == 0) {
		if (cmd->handler(conn, conn->data, cmd->args))
			return (false);
		free(cmd->args);
		list_pop(player->cmd_queue);
	}
	return (true);
}
