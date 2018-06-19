/*
** EPITECH PROJECT, 2018
** cmd inventory
** File description:
** cmd inventory
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_inventory(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
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
