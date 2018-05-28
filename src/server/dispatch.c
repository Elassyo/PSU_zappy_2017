/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Command dispatcher
*/

#include <string.h>

#include "zappy_server.h"

static zpy_srv_cmd_t const zpy_srv_cmds[] = {
	{ NULL, NULL }
};

bool zpy_srv_dispatch_cmd(tcp_server_conn_t *conn,
	char const *cmd, char const *args)
{
	zpy_srv_client_t *client = conn->data;

	for (size_t i = 0; zpy_srv_cmds[i].str != NULL; i++) {
		if (strcasecmp(cmd, zpy_srv_cmds[i].str) != 0)
			continue;
		/* add more checks if necessary */
		return (zpy_srv_cmds[i].handler(conn, client, args));
	}
	/* TODO: unknown command -> reply "ko" */
	return (true);
}
