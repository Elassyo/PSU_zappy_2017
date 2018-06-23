/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Set command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_set(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	char const *items[NITEM_TYPES] = { "food", "linemate",
		"deraumere", "sibur", "mendiane", "phiras", "thystame" };
	bool res = false;

	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		if (strcasecmp(items[i], args) != 0)
			continue;
		res = zpy_srv_player_item_drop(
			client->server, client->player, i);
		tcp_conn_printf(conn, res ? "ok\n" : "ko\n");
		return (true);
	}
	tcp_conn_printf(conn, "ko\n");
	return (true);
}
