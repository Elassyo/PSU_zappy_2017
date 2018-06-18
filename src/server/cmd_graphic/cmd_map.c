/*
** EPITECH PROJECT, 2018
** cmd map
** File description:
** cmd map
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

bool cmd_msz(tcp_conn_t *conn,
		zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
{
	char buff[256];

	snprintf(buff, 256, "msz %u %u\n", client->server->map.width,
		client->server->map.height);
	cbuf_write(&conn->out, &buff, strlen(buff));
	return (true);
}

bool cmd_bct(tcp_conn_t *conn,
		zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
{
	char buff[256];

	snprintf(buff, 256, "msz %u %u\n", client->server->map.width,
		client->server->map.height);
	cbuf_write(&conn->out, &buff, strlen(buff));
	return (true);
}
