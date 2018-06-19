/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player and items interactions
*/

#include <stdlib.h>

#include "zappy_server.h"

bool zpy_srv_player_item_take(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type)
{
	int i;
	zpy_srv_item_group_t *item_group;

	i = zpy_srv_map_find_item_group_idx(map,
		player->x, player->y, item_type);
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
	if (player->inventory[item_type] == 0)
		return (false);
	if (!zpy_srv_map_add_item(map, player->x, player->y, item_type))
		return (false);
	player->inventory[item_type]--;
	return (true);
}
