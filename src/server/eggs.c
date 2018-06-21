/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** server egg handling routines
*/

#include <stdlib.h>

#include "zappy_server.h"

bool zpy_srv_egg_new(zpy_srv_t *server, zpy_srv_player_t *parent)
{
	zpy_srv_egg_t *egg;

	egg = malloc(sizeof(*egg));
	if (egg == NULL)
		return (false);
	egg->id = ++server->last_egg_id;
	egg->parent_id = parent->id;
	egg->x = parent->x;
	egg->y = parent->y;
	egg->countdown = 600;
	egg->team = parent->team;
	egg->hatched = false;
	list_push_back(server->eggs, egg);
	zpy_srv_grph_sendall(server, &zpy_srv_grph_enw, egg);
	return (true);
}

bool zpy_srv_egg_use_hatched(zpy_srv_t *server, unsigned short team,
	int *x, int *y)
{
	unsigned int i = 0;
	list_node_t *node;
	zpy_srv_egg_t *egg;

	node = server->eggs->head;
	while (node) {
		egg = node->data;
		if (egg->team == team && egg->hatched) {
			*x = egg->x;
			*y = egg->y;
			zpy_srv_grph_sendall(server, &zpy_srv_grph_ebo, egg);
			list_remove(server->eggs, i);
			return (true);
		}
		node = node->next;
		i++;
	}
	return (false);
}

void zpy_srv_eggs_tick(zpy_srv_t *server)
{
	list_node_t *node;
	zpy_srv_egg_t *egg;

	node = server->eggs->head;
	while (node) {
		egg = node->data;
		if (!egg->hatched && egg->countdown-- <= 1) {
			egg->hatched = true;
			zpy_srv_grph_sendall(server, &zpy_srv_grph_eht, egg);
		}
		node = node->next;
	}
}
