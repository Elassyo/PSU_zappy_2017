/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map initialization and destruction
*/

#include <stddef.h>
#include <stdlib.h>

#include "zappy_server.h"

bool zpy_srv_map_init(zpy_srv_map_t *map)
{
	map->players = list_create(false);
	map->items = list_create(true);
	if (map->players == NULL || map->items == NULL)
		return (false);
	return (true);
}

void zpy_srv_map_cleanup(zpy_srv_map_t *map)
{
	list_destroy(map->players);
	list_destroy(map->items);
}

int zpy_srv_map_find_item_group(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type)
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

bool zpy_srv_map_add_item(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type)
{
	int i;
	zpy_srv_item_group_t *item_group;

	i = zpy_srv_map_find_item_group(map, x, y, item_type);
	if (i < 0) {
		item_group = malloc(sizeof(*item_group));
		if (item_group == NULL)
			return (false);
		item_group->x = x;
		item_group->y = y;
		item_group->type = item_type;
		item_group->amount = 0;
		list_push_back(map->items, item_group);
	} else {
		item_group = list_get(map->items, i);
	}
	item_group->amount++;
	return (true);
}

void zpy_srv_map_fill(zpy_srv_t *srv)
{
	unsigned int res_amt;
	unsigned int x;
	unsigned int y;
	zpy_item_type_t resource;

	res_amt = 5 * srv->max_players + ((rand() % 2 * srv->max_players) -
		srv->max_players);
	for (unsigned int i = 0; i < res_amt; i++) {
		x = rand() % srv->map.width;
		y = rand() % srv->map.height;
		resource = (zpy_item_type_t) (rand() % (NITEM_TYPES - 1));
		zpy_srv_map_add_item(&srv->map, x, y, resource);
		x = rand() % srv->map.width;
		y = rand() % srv->map.height;
		zpy_srv_map_add_item(&srv->map, x, y, FOOD);
	}
}
