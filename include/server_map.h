/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** server map handling
*/

#ifndef SERVER_MAP_H_
	#define SERVER_MAP_H_

	#include <stddef.h>
	#include "aled_list.h"

typedef enum direction_e {
	UP,
	RIGHT,
	DOWN,
	LEFT
} direction_t;

typedef enum item_e {
	FOOD = 0,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
} item_t;

typedef struct player_s {
	size_t team;
	ssize_t pos_x;
	ssize_t pos_y;
	direction_t direction;
	size_t level;
	size_t items[THYSTAME + 1];
	size_t food_amount;
	size_t food_countdown;
	size_t action_countdown;
} player_t;

typedef struct item_group_s {
	item_t type;
	size_t amount;
} item_group_t;

typedef struct server_map_s {
	size_t width;
	size_t height;
	aled_list_t ***cells;
	aled_list_t *players;
} server_map_t;

server_map_t	*server_map_init(size_t width, size_t height);
void		server_map_add_player(server_map_t *map, size_t team);
int		player_drop_object(server_map_t *map, player_t *player,
					item_t item);
int		player_take_object(server_map_t *map, player_t *player,
					item_t item);
void		player_move_forward(server_map_t *map, player_t *player);
void		player_turn_left(player_t *player);
void		player_turn_right(player_t *player);

#endif /* !SERVER_MAP_H_ */
