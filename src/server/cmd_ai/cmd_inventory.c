/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Inventory command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_inventory(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	zpy_srv_player_t *player = client->player;
	char const *items[NITEM_TYPES] = { "food", "linemate",
		"deraumere", "sibur", "mendiane", "phiras", "thystame" };

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	tcp_conn_printf(conn, "[ ");
	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		if (i > 0)
			tcp_conn_printf(conn, ", ");
		tcp_conn_printf(conn, "%s %u", items[i], player->inventory[i]);
	}
	tcp_conn_printf(conn, " ]\n");
	return (true);
}
