/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MCT command
*/

#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_mct(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	zpy_srv_grph_mct(conn, &client->server->map);
	return (true);
}
