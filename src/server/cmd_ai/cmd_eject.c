/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Eject command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

static void zpy_srv_player_eject_forward(zpy_srv_map_t *map,
	zpy_srv_player_t *player, zpy_direction_t direction)
{
	zpy_srv_player_move(map, player, direction);
	tcp_conn_printf(player->conn, "eject: %u\n",
			((direction + 2) % NDIRECTIONS + 1));
}

static bool can_eject(zpy_srv_player_t *player1, zpy_srv_player_t *player2)
{
	return (player1->id != player2->id &&
		player1->x == player2->x &&
		player1->y == player2->y);
}

bool zpy_srv_cmd_eject(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	list_node_t *node;
	zpy_srv_player_t *player;
	unsigned int ejected = 0;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	node = client->server->map.players->head;
	while (node != NULL) {
		player = node->data;
		if (can_eject(client->player, player)) {
			zpy_srv_player_eject_forward(&client->server->map,
				player, client->player->direction);
			ejected++;
		}
		node = node->next;
	}
	tcp_conn_printf(conn, ejected > 0 ? "ok\n" : "ko\n");
	return (true);
}
