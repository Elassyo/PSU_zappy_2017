/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Incantation function that valid if the incantation is Ok or not
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"
#include "zappy.h"

static zpy_ritual_t const zpy_srv_ritual_steps[] = {
	{ 1, "0100000" },
	{ 2, "0111000" },
	{ 2, "0201020" },
	{ 4, "0112010" },
	{ 4, "0121300" },
	{ 6, "0123010" },
	{ 6, "0222221" }
};

static zpy_ritual_t zpy_srv_get_ritual(zpy_srv_player_t *player)
{
	for (int i = 0; i < 8; i++) {
		if (player->level == i + 1) {
			return (zpy_srv_ritual_steps[i]);
		}
	}
	return (zpy_srv_ritual_steps[0]);
}

static char *zpy_srv_get_content_map(zpy_srv_map_t *map, unsigned int x,
		unsigned int y)
{
	char items_floor[NITEM_TYPES];
	list_node_t *node = map->items->head;
	zpy_srv_item_group_t *item_group;

	memset(items_floor, '0', NITEM_TYPES);
	while (node != NULL) {
		item_group = node->data;
		if (item_group->x == x && item_group->y == y
		&& items_floor[item_group->type] < 100) {
			items_floor[item_group->type] += 1;
		}
		node = node->next;
	}
	return (strdup(items_floor));
}

list_t *zpy_srv_get_player_same_level(zpy_srv_client_t *client)
{
	list_t *players = zpy_srv_map_players_on_tile(&(client->server->map),
			client->player->x, client->player->y);
	list_node_t *it = players->head;
	list_t *ret = list_create(false);
	zpy_srv_player_t *player = client->player;

	while (it) {
		if (((zpy_srv_player_t*)(it->data))->level == player->level)
			list_push_back(ret, it->data);
		it = it->next;
	}
	return (ret);
}

bool zpy_srv_is_incantation_ok(zpy_srv_client_t *client)
{
	zpy_ritual_t ritual = zpy_srv_get_ritual(client->player);
	char *items_floor = zpy_srv_get_content_map(&(client->server->map),
			client->player->x, client->player->y);
	unsigned short level = client->player->level;
	list_t *players = zpy_srv_get_player_same_level(client);
	unsigned int nb_players = players->len;

	if (ritual.nb_players != nb_players || strcmp(ritual.items + 1,
						     items_floor + 1) != 0)
		return (false);
	return (true);
}
