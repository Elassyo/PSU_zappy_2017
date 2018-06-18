/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player and items interactions
*/

#include <stdlib.h>

#include "zappy_server.h"

static int zpy_srv_map_find_item_group(zpy_srv_map_t *map,
	unsigned int x, unsigned int y,
	zpy_item_type_t item_type)
{
	unsigned int i = 0;
	list_node_t *node = map->items->head;
	zpy_srv_item_group_t *item_group;

	while (node != NULL) {
		item_group = node->data;
		if (item_group->x == x && item_group->y == y &&
			item_group->type == item_type)
			return (i);
		node = node->next;
		i++;
	}
	return (-1);
}

bool zpy_srv_player_item_take(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type)
{
	int i;
	zpy_srv_item_group_t *item_group;

	i = zpy_srv_map_find_item_group(map, player->x, player->y, item_type);
	if (i < 0)
		return (false);
	item_group = list_get(map->items, i);
	if (--item_group->amount == 0)
		list_remove(map->items, i);
	player->inventory[item_type]++;
	return (true);
}

bool zpy_srv_player_item_drop(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type)
{
	int i;
	zpy_srv_item_group_t *item_group;

	if (player->inventory[item_type] == 0)
		return (false);
	i = zpy_srv_map_find_item_group(map, player->x, player->y, item_type);
	if (i < 0) {
		item_group = malloc(sizeof(*item_group));
		item_group->x = player->x;
		item_group->y = player->y;
		item_group->type = item_type;
		item_group->amount = 0;
		list_push_back(map->items, item_group);
	} else {
		item_group = list_get(map->items, i);
	}
	item_group->amount++;
	player->inventory[item_type]--;
	return (true);
}
