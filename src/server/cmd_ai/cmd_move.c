/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Movement commands (Forward, Left and Right)
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_forward(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	zpy_srv_player_move_forward(&(client->server->map), client->player);
	tcp_conn_printf(conn, "ok\n");
	return (true);
}

bool zpy_srv_cmd_left(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	zpy_srv_player_turn_left(client->player);
	tcp_conn_printf(conn, "ok\n");
	return (true);
}

bool zpy_srv_cmd_right(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	zpy_srv_player_turn_right(client->player);
	tcp_conn_printf(conn, "ok\n");
	return (true);
}
