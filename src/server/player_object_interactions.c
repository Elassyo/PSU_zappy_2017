/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** take/drop objects
*/

#include "server_map.h"

static item_group_t *find_item_group(aled_list_t *items, item_t item)
{
	item_group_t *ret;

	for (size_t i = 0; i < items->len; i++) {
		ret = aled_list_get(items, i);
		if (ret->type == item) {
			return (ret);
		}
	}
	return (NULL);
}

int player_take_object(server_map_t *map, player_t *player, item_t item)
{
	aled_list_t *items = map->cells[player->pos_x][player->pos_y];
	item_group_t *map_item = find_item_group(items, item);

	if (map_item == NULL)
		return (1);
	player->items[item]++;
	return (0);
}

int player_drop_object(server_map_t *map, player_t *player, item_t item)
{
	aled_list_t *items = map->cells[player->pos_x][player->pos_y];
	item_group_t *map_item = find_item_group(items, item);

	if (player->items[item] == 0)
		return (1);
	if (map_item == NULL) {
		map_item = malloc(sizeof(*map_item));
		map_item->type = item;
		map_item->amount = 0;
	}
	map_item->amount++;
	player->items[item]--;
	return (0);
}
