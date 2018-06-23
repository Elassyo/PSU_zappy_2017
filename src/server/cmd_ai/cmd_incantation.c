/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Incantation command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"
#include "zappy.h"

static bool zpy_srv_cmd_incantation_finish(
	tcp_conn_t *conn __attribute__ ((unused)), zpy_srv_client_t *client,
	char const *args __attribute__ ((unused)))
{
	bool incantation_res;
	list_node_t *node;
	zpy_srv_player_t *player;

	incantation_res = zpy_srv_incantation_ok(client);
	node = zpy_srv_incantation_same_level_players(client)->head;
	while (node != NULL) {
		player = node->data;
		if (incantation_res == true) {
			player->level += 1;
			tcp_conn_printf(player->conn, "Current level: %u\n",
				player->level);
		} else {
			tcp_conn_printf(player->conn, "ko\n");
		}
		node = node->next;
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
	list_push_back(client->player->cmd_queue, cmd);
	return (true);
}
