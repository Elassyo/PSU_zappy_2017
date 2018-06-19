/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Take command
*/

#include <stdio.h>
#include <strings.h>

#include "zappy_server.h"

bool zpy_srv_cmd_take(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	char *items[NITEM_TYPES] = { "food", "linemate", "deraumere",
				"sibur", "mendiane", "phiras", "thystame" };
	bool res = false;

	for (unsigned short i = 0; i < NITEM_TYPES; i++) {
		if (!strcasecmp(items[i], args)) {
			res = zpy_srv_player_item_take(&(client->server->map),
						client->player, i);
		}
	}
	if (res == true)
		tcp_conn_printf(conn, "ok\n");
	else
		tcp_conn_printf(conn, "ko\n");
	return (true);
}
