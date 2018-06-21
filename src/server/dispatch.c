/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Command dispatcher
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

static zpy_srv_cmd_t const zpy_srv_cmds[] = {
	{ "forward", &zpy_srv_cmd_forward, CLIENT_AI, 7, NULL },
	{ "right", &zpy_srv_cmd_right, CLIENT_AI, 7, NULL },
	{ "left", &zpy_srv_cmd_left, CLIENT_AI, 7, NULL },
	{ "look", &zpy_srv_cmd_look, CLIENT_AI, 7, NULL },
	{ "inventory", &zpy_srv_cmd_inventory, CLIENT_AI, 1, NULL },
	{ "broadcast", &zpy_srv_cmd_broadcast, CLIENT_AI, 7, NULL },
	{ "connect_nbr", &zpy_srv_cmd_connect, CLIENT_AI, 0, NULL },
	{ "fork", &zpy_srv_cmd_fork, CLIENT_AI, 42, NULL },
	{ "eject", &zpy_srv_cmd_eject, CLIENT_AI, 7, NULL },
	{ "take", &zpy_srv_cmd_take, CLIENT_AI, 7, NULL },
	{ "set", &zpy_srv_cmd_set, CLIENT_AI, 7, NULL },
	{ "incantation", &zpy_srv_cmd_incantation, CLIENT_AI, 0, NULL },
	{ "msz", &zpy_srv_cmd_msz, CLIENT_GRAPHIC, 0, NULL },
	{ "bct", &zpy_srv_cmd_bct, CLIENT_GRAPHIC, 0, NULL },
	{ "mct", &zpy_srv_cmd_mct, CLIENT_GRAPHIC, 0, NULL },
	{ "pin", &zpy_srv_cmd_pin, CLIENT_GRAPHIC, 0, NULL },
	{ "plv", &zpy_srv_cmd_plv, CLIENT_GRAPHIC, 0, NULL },
	{ "ppo", &zpy_srv_cmd_ppo, CLIENT_GRAPHIC, 0, NULL },
	{ "sgt", &zpy_srv_cmd_sgt, CLIENT_GRAPHIC, 0, NULL },
	{ "sst", &zpy_srv_cmd_sst, CLIENT_GRAPHIC, 0, NULL },
	{ "tna", &zpy_srv_cmd_tna, CLIENT_GRAPHIC, 0, NULL },
	{ NULL, NULL, CLIENT_UNKNOWN, 0, NULL }
};

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *cmd, char const *args)
{
	zpy_srv_cmd_t *c;

	for (size_t i = 0; zpy_srv_cmds[i].str != NULL; i++) {
		if (strcasecmp(cmd, zpy_srv_cmds[i].str) != 0)
			continue;
		if (client->type != zpy_srv_cmds[i].client_type)
			break;
		if (client->type == CLIENT_GRAPHIC)
			return (zpy_srv_cmds[i].handler(conn, client, args));
		c = malloc(sizeof(*c));
		if (!c)
			return (false);
		memcpy(c, &zpy_srv_cmds[i], sizeof(*c));
		c->args = strdup(args);
		list_push_back(client->player->cmd_queue, c);
		return (true);
	}
	tcp_conn_printf(conn, client->type == CLIENT_AI ? "ko\n" : "suc\n");
	return (true);
}
