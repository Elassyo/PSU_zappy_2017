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
	egg->countdown = 600;
	egg->team = parent->team;
	return (egg);
}

static void zpy_srv_egg_hatch(zpy_srv_t *server, zpy_srv_egg_t *egg,
	unsigned int i)
{
	zpy_srv_team_t *team;

	for (size_t i = 0; i < server->teams->len; i++) {
		team = list_get(server->teams, i);
		if (i == egg->id)
			team->max_players++;
	}
	list_remove(server->eggs, i);
}

void zpy_srv_tick_eggs(zpy_srv_t *server)
{
	list_node_t *it = server->eggs->head;
	zpy_srv_egg_t *egg;

	while (it) {
		egg = it->data;
		if (!egg)
			continue;
		egg->countdown--;
		it = it->next;
	}
	for (unsigned int i = 0; i < server->eggs->len; i++) {
		egg = list_get(server->eggs, i);
		if (egg->countdown == 0) {
			zpy_srv_egg_hatch(server, egg, i);
			i--;
		}
	}
}
