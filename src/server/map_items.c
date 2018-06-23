/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map items
*/

#include <stdlib.h>

#include "zappy_server.h"

zpy_srv_item_group_t *zpy_srv_map_find_item_group(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type)
{
	list_node_t *node = map->items->head;
	zpy_srv_item_group_t *item_group;

	while (node != NULL) {
		item_group = node->data;
		if (item_group->x == x && item_group->y == y &&
			item_group->type == item_type)
			return (item_group);
		node = node->next;
	}
	return (NULL);
}

int zpy_srv_map_find_item_group_idx(zpy_srv_map_t *map,
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

bool zpy_srv_map_add_item(zpy_srv_t *server,
	unsigned int x, unsigned int y, zpy_item_type_t item_type)
{
	zpy_srv_item_group_t *item_group;

	item_group = zpy_srv_map_find_item_group(&server->map, x, y, item_type);
	if (item_group == NULL) {
		item_group = malloc(sizeof(*item_group));
		if (item_group == NULL)
			return (false);
		item_group->x = x;
		item_group->y = y;
		item_group->type = item_type;
		item_group->amount = 0;
		list_push_back(server->map.items, item_group);
	}
	item_group->amount++;
	zpy_srv_grph_sendall(server, &zpy_srv_grph_bct, x, y);
	return (true);
}

bool zpy_srv_map_remove_item(zpy_srv_t *server,
	unsigned int x, unsigned int y, zpy_item_type_t item_type)
{
	int i;
	zpy_srv_item_group_t *item_group;

	i = zpy_srv_map_find_item_group_idx(&server->map, x, y, item_type);
	if (i < 0)
		return (false);
	item_group = list_get(server->map.items, i);
	if (--item_group->amount == 0)
		list_remove(server->map.items, i);

	zpy_srv_grph_sendall(server, &zpy_srv_grph_bct, x, y);
	return (true);
}
