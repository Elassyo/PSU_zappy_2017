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
	zpy_srv_player_t *player, zpy_direction_t eject_dir)
{
	unsigned int dirs[4] = { 5, 3, 1, 7 };

	zpy_srv_player_move(map, player, eject_dir);
	tcp_conn_printf(player->conn, "eject: %u\n",
		dirs[MOD(eject_dir - player->direction, NDIRECTIONS)]);
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
	list_node_t *n;
	unsigned int ejected = 0;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	for (n = client->server->map.players->head; n; n = n->next) {
		if (can_eject(client->player, n->data)) {
			zpy_srv_player_eject_forward(&client->server->map,
				n->data, client->player->direction);
			ejected++;
		}
	}
	if (ejected > 0)
		zpy_srv_grph_sendall(client->server,
			&zpy_srv_grph_pex, client->player);
	tcp_conn_printf(conn, ejected > 0 ? "ok\n" : "ko\n");
	return (true);
}
