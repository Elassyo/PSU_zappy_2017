/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** server egg handling routines
*/

#include <stdlib.h>

#include "zappy_server.h"

zpy_srv_egg_t *zpy_srv_egg_init(size_t *id, zpy_srv_player_t *parent)
{
	zpy_srv_egg_t *egg = malloc(sizeof(*egg));

	egg->id = (*id)++;
	egg->creator_id = parent->id;
	egg->x = parent->x;
	egg->y = parent->y;
	egg->team = parent->team;
}
