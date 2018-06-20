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
					zpy_srv_player_t *player,
					zpy_direction_t direction)
{
	switch (direction) {
	case UP:
		player->y = (player->y + map->height - 1) % map->height;
		break;
	case DOWN:
		player->y = (player->y + 1) % map->height;
		break;
	case LEFT:
		player->x = (player->x + map->width - 1) % map->width;
		break;
	case RIGHT:
		player->x = (player->x + 1) % map->width;
		break;
	default:
		break;
	}
	tcp_conn_printf(player->conn, "eject: %u\n",
			((direction + 2) % NDIRECTIONS + 1));
}

static bool is_different(zpy_srv_player_t *player1, zpy_srv_player_t *player2)
{
	if (player1->id != player2->id &&
			player1->x == player2->x &&
			player1->y == player2->y)
		return (true);
	return (false);
}

bool zpy_srv_cmd_eject(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	list_node_t *clients = client->server->map.players->head;
	zpy_srv_player_t *player;
	int i = 0;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	for (; clients != NULL; clients = clients->next) {
		player = clients->data;
		if (is_different(player, client->player) == true) {
			zpy_srv_player_eject_forward(&(client->server->map),
					player, client->player->direction);
			zpy_srv_grph_sendall(client->server, &zpy_srv_grph_pex,
					player);
			i++;
		}
	}
	i > 0 ? tcp_conn_printf(conn, "ok\n") : tcp_conn_printf(conn, "ko\n");
	return (true);
}
