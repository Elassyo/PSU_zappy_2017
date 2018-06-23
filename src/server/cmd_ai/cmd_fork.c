/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Fork command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_fork(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	tcp_conn_printf(conn, "ok\n");
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pfk, client->player);
	zpy_srv_egg_new(client->server, client->player);
	return (true);
}
