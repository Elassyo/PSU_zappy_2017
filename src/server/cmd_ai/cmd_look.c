/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Look command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

static void zpy_srv_look_tile(tcp_conn_t *conn, zpy_srv_client_t *client,
	size_t pos)
{
	zpy_srv_map_t *map = &client->server->map;
	size_t x = pos % map->width;
	size_t y = pos / map->width;
	char const *items[NITEM_TYPES] = { "food", "linemate",
		"deraumere", "sibur", "mendiane", "phiras", "thystame" };
	zpy_srv_item_group_t *item_group;
	list_t *players = zpy_srv_map_players_on_tile(map, x, y);

	for (size_t i = 0; i < players->len; i++) {
		tcp_conn_printf(conn, " player");
	}
	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		item_group = zpy_srv_map_find_item_group(map, x, y, i);
		for (size_t j = 1; item_group && j < item_group->amount; j++)
			tcp_conn_printf(conn, " %s", items[i]);
	}
	list_destroy(players);
}

bool zpy_srv_cmd_look(tcp_conn_t *conn, zpy_srv_client_t *client,
		char const *args)
{
	size_t pos;

	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	tcp_conn_printf(conn, "[ player,");
	for (size_t i = 0;; i++) {
		pos = zpy_srv_get_vision_tile_pos(&client->server->map,
				client->player, i);
		if (pos / client->server->map.width >= client->player->level)
			break;
		else if (pos > 0)
			tcp_conn_printf(conn, ",");
		zpy_srv_look_tile(conn, client, pos);
	}
	tcp_conn_printf(conn, " ]\n");
	return (true);
}
