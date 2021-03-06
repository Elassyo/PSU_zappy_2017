/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Incantation command
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "zappy_server.h"
#include "zappy.h"

static short zpy_srv_incantation_team_win(zpy_srv_t *server)
{
	list_node_t *n_t;
	list_node_t *n_p;
	zpy_srv_team_t *team;
	zpy_srv_player_t *player;
	unsigned int i = 0;

	for (n_t = server->teams->head; n_t; n_t = n_t->next) {
		team = n_t->data;
		i = 0;
		for (n_p = team->players->head; n_p; n_p = n_p->next) {
			player = n_p->data;
			i += player->level == 8 ? 1 : 0;
		}
		if (i >= 6)
			return (player->team);
	}
	return (-1);
}

static void zpy_srv_incantation_send_result(zpy_srv_client_t *client, bool res)
{
	list_t *players;
	zpy_srv_player_t *player;

	players = zpy_srv_incantation_players(client);
	for (list_node_t *node = players->head; node; node = node->next) {
		player = node->data;
		if (res) {
			tcp_conn_printf(player->conn,
				"Current level: %u\n", ++player->level);
			zpy_srv_grph_sendall(client->server,
				&zpy_srv_grph_plv, player);
		} else {
			tcp_conn_printf(player->conn, "ko\n");
		}
	}
	list_destroy(players);
}

static bool zpy_srv_cmd_incantation_finish(
	tcp_conn_t *conn __attribute__ ((unused)), zpy_srv_client_t *client,
	char const *args __attribute__ ((unused)))
{
	bool res;
	short win;

	res = zpy_srv_incantation_ok(client);
	if (res)
		zpy_srv_incantation_clear(client);
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pie,
		client->player->x, client->player->y, res);
	zpy_srv_incantation_send_result(client, res);

	win = zpy_srv_incantation_team_win(client->server);
	if (win >= 0) {
		zpy_srv_grph_sendall(client->server, &zpy_srv_grph_seg, win);
		kill(getpid(), SIGINT);
	}
	return (true);
}

bool zpy_srv_cmd_incantation(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	zpy_srv_cmd_t *cmd;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (false);
	cmd->args = NULL;
	cmd->handler = &zpy_srv_cmd_incantation_finish;
	cmd->countdown = 300;
	if (zpy_srv_incantation_ok(client) == true)
		tcp_conn_printf(conn, "Elevation underway\n");
	else
		tcp_conn_printf(conn, "ko\n");
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pic, client);
	list_push_back(client->player->cmd_queue, cmd);
	return (true);
}
