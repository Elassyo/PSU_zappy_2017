/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Look command
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

static void zpy_srv_cmd_look_warp_off(zpy_srv_client_t *client, int *x, int *y)
{
	*x = MOD(*x, client->server->map.width);
	*y = MOD(*y, client->server->map.height);
}

static void zpy_srv_cmd_look_tile_pos(zpy_srv_client_t *client, unsigned int i,
	unsigned int *x, unsigned int *y)
{
	int x_off = 0;
	int y_off = 0;

	if (i != 0) {
		y_off = (int)(i / sqrt(i));
		x_off = -y_off + i - y_off * y_off;
	}
	if (client->player->direction > RIGHT) {
		x_off = -x_off;
		y_off = -y_off;
	}
	if (client->player->direction % 2 == 0) {
		zpy_srv_cmd_look_warp_off(client, &x_off, &y_off);
		*x = MOD(client->player->x + x_off, client->server->map.width);
		*y = MOD(client->player->y - y_off, client->server->map.height);
	} else {
		zpy_srv_cmd_look_warp_off(client, &y_off, &x_off);
		*x = MOD(client->player->x + y_off, client->server->map.height);
		*y = MOD(client->player->y + x_off, client->server->map.width);
	}
}

static void zpy_srv_cmd_look_tile(tcp_conn_t *conn, zpy_srv_client_t *client,
	unsigned int x, unsigned int y)
{
	zpy_srv_map_t *map = &client->server->map;
	char const *items[NITEM_TYPES] = { "food", "linemate",
		"deraumere", "sibur", "mendiane", "phiras", "thystame" };
	zpy_srv_item_group_t *item_group;
	list_t *players;

	players = zpy_srv_map_players_on_tile(map, x, y);
	for (size_t i = 0; i < players->len; i++)
		tcp_conn_printf(conn, " player");
	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		item_group = zpy_srv_map_find_item_group(map, x, y, i);
		if (item_group == NULL)
			continue;
		for (unsigned char j = 0; j < item_group->amount; j++)
			tcp_conn_printf(conn, " %s", items[i]);
	}
	list_destroy(players);
}

bool zpy_srv_cmd_look(tcp_conn_t *conn, zpy_srv_client_t *client,
		char const *args)
{
	unsigned int x;
	unsigned int y;
	unsigned int range;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	range = U((client->player->level + 1) * (client->player->level + 1));
	tcp_conn_printf(conn, "[");
	for (unsigned int i = 0; i < range; i++) {
		if (i > 0)
			tcp_conn_printf(conn, ",");
		zpy_srv_cmd_look_tile_pos(client, i, &x, &y);
		zpy_srv_cmd_look_tile(conn, client, x, y);
	}
	tcp_conn_printf(conn, " ]\n");
	return (true);
}
