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
	{ 1, "100000" },
	{ 2, "111000" },
	{ 2, "201020" },
	{ 4, "112010" },
	{ 4, "121300" },
	{ 6, "123010" },
	{ 6, "222221" }
};

static char *zpy_srv_incantation_map_content(zpy_srv_map_t *map,
	unsigned int x, unsigned int y)
{
	char items_floor[NITEM_TYPES - 1];
	list_node_t *node;
	zpy_srv_item_group_t *item_group;

	memset(items_floor, '0', NITEM_TYPES - 1);
	node = map->items->head;
	while (node != NULL) {
		item_group = node->data;
		if (item_group->x == x && item_group->y == y &&
			items_floor[item_group->type - 1] < '9' &&
			item_group->type != FOOD) {
			items_floor[item_group->type - 1] += 1;
		}
		node = node->next;
	}
	return (strdup(items_floor));
}

list_t *zpy_srv_incantation_same_level_players(zpy_srv_client_t *client)
{
	list_t *players;
	list_node_t *node;
	zpy_srv_player_t *player;
	list_t *ret;

	players = zpy_srv_map_players_on_tile(&client->server->map,
		client->player->x, client->player->y);
	node = players->head;
	ret = list_create(false);
	while (node != NULL) {
		player = node->data;
		if (client->player->level == player->level)
			list_push_back(ret, node->data);
		node = node->next;
	}
	list_destroy(players);
	return (ret);
}

bool zpy_srv_incantation_ok(zpy_srv_client_t *client)
{
	zpy_ritual_t ritual = zpy_srv_ritual_steps[client->player->level - 1];
	char *floor_items = zpy_srv_incantation_map_content(
		&client->server->map, client->player->x, client->player->y);
	list_t *players;
	bool res;

	players = zpy_srv_incantation_same_level_players(client);
	res = ritual.nb_players != players->len ||
		strcmp(ritual.items, floor_items) != 0;
	list_destroy(players);
	free(floor_items);
	return (res);
}
