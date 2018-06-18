/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Command dispatcher
*/

#include <stdlib.h>
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
	{ "Forward", &cmd_forward, CLIENT_AI, 0, NULL },
	{ "Right", &cmd_right, CLIENT_AI, 0, NULL },
	{ "Left", &cmd_left, CLIENT_AI, 0, NULL },
	{ "Look", &cmd_look, CLIENT_AI, 0, NULL },
	{ "Inventory", &cmd_inventory, CLIENT_AI, 0, NULL },
	{ "Broadcast", &cmd_broadcast, CLIENT_AI, 0, NULL },
	{ "Connect_nbr", &cmd_connect, CLIENT_AI, 0, NULL },
	{ "Fork", &cmd_fork, CLIENT_AI, 0, NULL },
	{ "Eject", &cmd_eject, CLIENT_AI, 0, NULL },
	{ "Take", &cmd_take, CLIENT_AI, 0, NULL },
	{ "Set", &cmd_set, CLIENT_AI, 0, NULL },
	{ "Incantation", &cmd_incantation, CLIENT_AI, 0, NULL },
	{ "msz", &cmd_msz, CLIENT_GRAPHIC, 0, NULL },
	{ "bct", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "mct", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "tna", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "ppo", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "plv", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "pin", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "sgt", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ "sst", &not_implemented, CLIENT_GRAPHIC, 0, NULL },
	{ NULL, NULL, CLIENT_UNKNOWN, 0, NULL }
};

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn, char const *cmd, char const *args)
{
	zpy_srv_client_t *client = conn->data;
	zpy_srv_cmd_t *c;

	for (size_t i = 0; zpy_srv_cmds[i].str != NULL; i++) {
		if (strcasecmp(cmd, zpy_srv_cmds[i].str) != 0)
			continue;
		if (client->type != zpy_srv_cmds[i].client_type)
			break;
		c = malloc(sizeof(*c));
		if (!c)
			return (false);
		memcpy(c, &zpy_srv_cmds[i], sizeof(*c));
		c->args = strdup(args);
		list_push_back(client->player->cmd_queue, c);
	}
	tcp_conn_write(conn, "ko\n", 3);
	printf("%s: Unknown command\n", cmd);
	return (true);
}
