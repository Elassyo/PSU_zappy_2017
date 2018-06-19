/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Inventory command
*/

#include <stdio.h>

#include "zappy_server.h"

bool zpy_srv_cmd_inventory(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	zpy_srv_player_t *player = client->player;
	char *items[NITEM_TYPES] = {"food", "linemate", "deraumere",
				"sibur", "mendiane", "phiras", "thystame"};

	for (unsigned short i = 0; i < NITEM_TYPES; i++) {
		printf("%s : %d", items[i], player->inventory[i]);
	}
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
