/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Vision handling routines
*/

#include "zappy_server.h"

static void zpy_srv_vision_tile_pos_direction(zpy_direction_t direction,
		int *pos_x, int *pos_y)
{
	int tmp;

	switch (direction) {
	case UP:
		*pos_x = -(*pos_x);
		*pos_y = -(*pos_y);
		break;
	case RIGHT:
		tmp = *pos_x;
		*pos_x = *pos_y;
		*pos_y = tmp;
		break;
	case LEFT:
		tmp = *pos_x;
		*pos_x = -(*pos_y);
		*pos_y = tmp;
		break;
	default:
		break;
	}
}

size_t zpy_srv_get_vision_tile_pos(zpy_srv_map_t *map,
		zpy_srv_player_t *player, size_t tile)
{
	int pos_x = 0;
	int pos_y = 0;
	int i = 0;
	int j = 1;

	while (U(i) < tile) {
		i++;
		if (i <= j) {
			j += j + 2;
			pos_y++;
			pos_x -= pos_x * 2 + 1;
		}
		pos_x++;
	}
	zpy_srv_vision_tile_pos_direction(player->direction, &pos_x, &pos_y);
	return (((pos_x + player->x) % map->width) * map->width
			+ ((pos_y + player->y) % map->height));
}
