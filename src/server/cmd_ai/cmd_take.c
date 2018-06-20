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
	bool res = false;

	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		if (strcasecmp(items[i], args) != 0)
			continue;
		res = zpy_srv_player_item_take(
			&client->server->map, client->player, i);
		if (res == true)
			zpy_srv_grph_sendall(client->server,
					&zpy_srv_grph_pgt, client->player, i);
		tcp_conn_printf(conn, res ? "ok\n" : "ko\n");
		return (true);
	}
	tcp_conn_printf(conn, "ko\n");
	return (true);
}
