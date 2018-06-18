/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Movement commands
*/

#include <stdio.h>

#include "zappy_server.h"

bool cmd_forward(tcp_conn_t *conn,
	zpy_srv_client_t *client,
	char const *cmd  __attribute__((unused)))
{
	zpy_srv_player_t *player = client->player;

	zpy_srv_player_move_forward(&(client->server->map), player);
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}

bool cmd_left(tcp_conn_t *conn,
	zpy_srv_client_t *client,
	char const *cmd  __attribute__((unused)))
{
	zpy_srv_player_t *player = client->player;

	zpy_srv_player_turn_left(player);
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}

bool cmd_right(tcp_conn_t *conn,
	zpy_srv_client_t *client,
	char const *cmd  __attribute__((unused)))
{
	zpy_srv_player_t *player = client->player;

	zpy_srv_player_turn_right(player);
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}
