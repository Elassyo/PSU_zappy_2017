/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TNA command
*/

#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_tna(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	zpy_srv_grph_send(conn, &zpy_srv_grph_tna, &client->server->teams);
	return (true);
}
