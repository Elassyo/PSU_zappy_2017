/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map command (MSZ and BCT)
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_msz(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args __attribute__ ((unused)))
{
	tcp_conn_printf(conn, "msz %u %u\n",
		client->server->map.width, client->server->map.height);
	return (true);
}

bool zpy_srv_cmd_bct(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	unsigned int x;
	unsigned int y;
	size_t rd;

	if (sscanf(args, "%u %u%zn", &x, &y, &rd) != 3 || rd != strlen(args) ||
		x >= client->server->map.width ||
		y >= client->server->map.height) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	tcp_conn_printf(conn, "bct %u %u %u %u %u %u %u %u %u\n", x, y,
		0, 0, 0, 0, 0, 0, 0);
	return (true);
}
