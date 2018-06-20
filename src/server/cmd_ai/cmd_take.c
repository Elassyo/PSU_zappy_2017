/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Take command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_take(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	char const *items[NITEM_TYPES] = { "food", "linemate",
		"deraumere", "sibur", "mendiane", "phiras", "thystame" };

	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		if (strcasecmp(items[i], args) != 0)
			continue;
		tcp_conn_printf(conn, zpy_srv_player_item_take(
			&client->server->map, client->player, i) ? "ok" : "ko");
		return (true);
	}
	tcp_conn_printf(conn, "ko\n");
	return (true);
}
