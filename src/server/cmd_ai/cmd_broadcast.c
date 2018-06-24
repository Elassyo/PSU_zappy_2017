/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Broadcast command
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

static unsigned int zpy_srv_cmd_broadcast_calc_dir(int x, int y)
{
	double quadrants[] = { 0.32175, 1.24905, 1.89255, 2.81984,
		3.46334, 4.49064, 5.03414, 5.96143 };
	double angle;

	angle = fmod(atan2(-y, -x) + 2 * M_PI, 2 * M_PI);
	for (unsigned int i = 0; i < 8; i++) {
		if (angle < quadrants[i])
			return (MOD(i - 2, 8));
	}
	return (7);
}

static void zpy_srv_cmd_broadcast_send(zpy_srv_client_t *client,
	zpy_srv_player_t *dest, char const *msg)
{
	int x;
	int y;
	unsigned int k = 0;

	x = dest->x - client->player->x;
	if (abs(x) > client->server->map.width / 2)
		x = (abs(x) - (int)client->server->map.width) * (x / abs(x));
	y = dest->y - client->player->y;
	if (abs(y) > client->server->map.height / 2)
		y = (abs(y) - (int)client->server->map.height) * (y / abs(y));
	if (x != 0 || y != 0) {
		k = zpy_srv_cmd_broadcast_calc_dir(x, y);
		k = MOD(k + 2 * dest->direction, 8) + 1;
	}
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
	tcp_conn_printf(conn, "ok\n");
	return (true);
}
