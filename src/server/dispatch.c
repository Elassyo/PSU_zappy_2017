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
	{ "Look", &cmd_look },
	{ "Inventory", &cmd_inventory },
	{ "Broadcast", &cmd_broadcast },
	{ "Connect_nbr", &cmd_connect },
	{ "Fork", &cmd_fork },
	{ "Eject", &cmd_eject },
	{ "Take", &cmd_take },
	{ "Set", &cmd_set },
	{ "Incantation", &cmd_incantation },
	{ "msz", &cmd_msz },
	{ "bct", &not_implemented },
	{ "mct", &not_implemented },
	{ "tna", &not_implemented },
	{ "ppo", &not_implemented },
	{ "plv", &not_implemented },
	{ "pin", &not_implemented },
	{ "sgt", &not_implemented },
	{ "sst", &not_implemented },
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
	tcp_conn_write(conn, "ko\n", 3);
	printf("%s: Unknown command\n", cmd);
	return (true);
}
