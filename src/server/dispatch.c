/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Command dispatcher
*/

#include <string.h>

#include "zappy_server.h"

////
#include <stdio.h>
static bool not_implemented(tcp_conn_t *conn __attribute__((unused)),
	zpy_srv_client_t *client __attribute__((unused)), char const *cmd)
{
	printf("%s: Command not implemented yet.\n", cmd);
	return (true);
}
////

static zpy_srv_cmd_t const zpy_srv_cmds[] = {
	{ "Forward", &cmd_forward, 7 },
	{ "Right", &cmd_right, 7 },
	{ "Left", &cmd_left, 7 },
	{ "Look", &not_implemented, 7 },
	{ "Inventory", &not_implemented, 1 },
	{ "Broadcast text", &not_implemented, 7 },
	{ "Connect_nbr", &not_implemented, 0 },
	{ "Fork", &not_implemented, 42 },
	{ "Eject", &not_implemented, 7 },
	{ "Take object", &not_implemented, 7 },
	{ "Set object", &not_implemented, 7 },
	{ "Incantation", &not_implemented, 300 },
	{ NULL, NULL, -1 }
};

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn, char const *cmd, char const *args)
{
	zpy_srv_client_t *client = conn->data;

	for (size_t i = 0; zpy_srv_cmds[i].str != NULL; i++) {
		if (strcasecmp(cmd, zpy_srv_cmds[i].str) != 0)
			continue;
		return (zpy_srv_cmds[i].handler(conn, client, args));
	}
	printf("%s: Unknown command\n", cmd);
	/* TODO: unknown command -> reply "ko" */
	return (true);
}
