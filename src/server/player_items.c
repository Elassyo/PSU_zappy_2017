/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player and items interactions
*/

#include <limits.h>
#include <stdlib.h>

#include "zappy_server.h"

bool zpy_srv_player_item_take(zpy_srv_t *server, zpy_srv_player_t *player,
	zpy_item_type_t item_type)
{
	if (!zpy_srv_map_remove_item(server, player->x, player->y, item_type))
		return (false);
	if (player->inventory[item_type] < UCHAR_MAX)
		player->inventory[item_type]++;
	zpy_srv_grph_sendall(server, &zpy_srv_grph_pgt, player, item_type);
	zpy_srv_grph_sendall(server, &zpy_srv_grph_pin, player);
	return (true);
}

bool zpy_srv_player_item_drop(zpy_srv_t *server, zpy_srv_player_t *player,
	zpy_item_type_t item_type)
{
	if (player->inventory[item_type] == 0)
		return (false);
	if (!zpy_srv_map_add_item(server, player->x, player->y, item_type))
		return (false);
	player->inventory[item_type]--;
	zpy_srv_grph_sendall(server, &zpy_srv_grph_pdr, player, item_type);
	zpy_srv_grph_sendall(server, &zpy_srv_grph_pin, player);
	return (true);
}
