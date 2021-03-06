/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Add and remove players from the map
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_player_new(zpy_srv_client_t *client, unsigned short team,
	int x, int y)
{
	client->player = malloc(sizeof(*client->player));
	if (client->player == NULL)
		return (false);
	client->player->cmd_queue = list_create(true);
	if (client->player->cmd_queue == NULL)
		return (false);
	client->player->id = ++client->server->last_player_id;
	client->player->team = team;
	client->player->x = x < 0 ? rand() % client->server->map.width : U(x);
	client->player->y = y < 0 ? rand() % client->server->map.height : U(y);
	client->player->direction = rand() % NDIRECTIONS;
	memset(client->player->inventory, 0, sizeof(client->player->inventory));
	client->player->inventory[FOOD] = 10;
	client->player->level = 1;
	client->player->food_countdown = 0;
	list_push_back(((zpy_srv_team_t*)list_get(client->server->teams,
		team))->players, client->player);
	list_push_back(client->server->map.players, client->player);
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pnw, client->player);
	return (true);
}

void zpy_srv_player_remove(zpy_srv_t *server, zpy_srv_player_t *player)
{
	zpy_srv_team_t *team;

	list_destroy(player->cmd_queue);
	list_remove(server->map.players,
		U(list_find(server->map.players, player, NULL)));
	team = list_get(server->teams, player->team);
	if (team->max_players > server->max_players)
		team->max_players--;
	list_remove(team->players,
		U(list_find(team->players, player, NULL)));
}

bool zpy_srv_player_tick(tcp_conn_t *conn, zpy_srv_player_t *player)
{
	zpy_srv_cmd_t *cmd;
	zpy_srv_client_t *client = conn->data;

	if (player->food_countdown-- <= 1) {
		if (--player->inventory[FOOD] == 0) {
			tcp_conn_printf(conn, "dead\n");
			return (false);
		}
		player->food_countdown = 126;
		zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pin, player);
	}
	cmd = list_get(player->cmd_queue, 0);
	if (cmd != NULL && cmd->countdown-- <= 1) {
		if (!cmd->handler(conn, conn->data, cmd->args))
			return (false);
		free(cmd->args);
		list_pop(player->cmd_queue);
	}
	return (true);
}

zpy_srv_player_t *zpy_srv_player_find(zpy_srv_map_t *map, unsigned int id)
{
	list_node_t *node;
	zpy_srv_player_t *player;

	node = map->players->head;
	while (node != NULL) {
		player = node->data;
		if (player->id == id)
			return (player);
		node = node->next;
	}
	return (NULL);
}
