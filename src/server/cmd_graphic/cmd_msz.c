/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MSZ command
*/

#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_msz(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	return (zpy_srv_grph_msz(conn, &client->server->map));
}
