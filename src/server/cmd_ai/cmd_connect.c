/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Connect_nbr command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_connect(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	zpy_srv_team_t *team;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	team = list_get(client->server->teams, client->player->team);
	tcp_conn_printf(conn, "%d\n", (team->max_players - team->players->len));
	return (true);
}
