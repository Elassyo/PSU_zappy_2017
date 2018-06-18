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
	{ "Look", &cmd_look, 7 },
	{ "Inventory", &cmd_inventory, 1 },
	{ "Broadcast", &cmd_broadcast, 7 },
	{ "Connect_nbr", &cmd_connect, 0 },
	{ "Fork", &cmd_fork, 42 },
	{ "Eject", &cmd_eject, 7 },
	{ "Take", &cmd_take, 7 },
	{ "Set", &cmd_set, 7 },
	{ "Incantation", &cmd_incantation, 300 },
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
	tcp_conn_write(conn, "ko\n", 3);
	printf("%s: Unknown command\n", cmd);
	return (true);
}
