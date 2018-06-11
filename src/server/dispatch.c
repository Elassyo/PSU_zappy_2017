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
	{ "Forward", &cmd_forward },
	{ "Right", &cmd_right },
	{ "Left", &cmd_left },
	{ "Look", &not_implemented },
	{ "Inventory", &not_implemented },
	{ "Broadcast text", &not_implemented },
	{ "Connect_nbr", &not_implemented },
	{ "Fork", &not_implemented },
	{ "Eject", &not_implemented },
	{ "Take object", &not_implemented },
	{ "Set object", &not_implemented },
	{ "Incantation", &not_implemented },
	{ NULL, NULL }
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
