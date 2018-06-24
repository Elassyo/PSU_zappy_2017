/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Broadcast command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

static unsigned int zpy_srv_cmd_broadcast_calc_dir(int x, int y,
	zpy_direction_t dir)
{
	unsigned int res = 0;

	return (res);
}

static void zpy_srv_cmd_broadcast_send(zpy_srv_client_t *client,
	zpy_srv_player_t *dest, char const *msg)
{
	int x;
	int y;
	unsigned int k = 0;

	x = dest->x - client->player->x;
	if (abs(x) > client->server->map.width / 2)
		x = (abs(x) - client->server->map.width) * x / abs(x);
	y = dest->y - client->player->y;
	if (abs(y) > client->server->map.width / 2)
		y = (abs(y) - client->server->map.width) * y / abs(y);
	if (x != 0 && y != 0)
		k = zpy_srv_cmd_broadcast_calc_dir(x, y, dest->direction);
	tcp_conn_printf(dest->conn, "message %u, %s\n", k, msg);
}

bool zpy_srv_cmd_broadcast(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	list_node_t *n;
	zpy_srv_player_t *player;

	if (strcmp(args, "") == 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pbc,
		client->player, args);
	for (n = client->server->map.players->head; n; n = n->next) {
		player = n->data;
		if (player == client->player)
			continue;
		zpy_srv_cmd_broadcast_send(client, player, args);
	}
	return (true);
}
