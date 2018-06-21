/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Incantation command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"
#include "zappy.h"

bool zpy_srv_incantation_step(tcp_conn_t *conn, zpy_srv_client_t *client,
			char const *args)
{
	list_t *players = zpy_srv_get_player_same_level(client);
	bool res = zpy_srv_is_incantation_ok(client);
	list_node_t *it = players->head;
	zpy_srv_player_t *pl = NULL;

	for (; it != NULL; it = it->next) {
		pl = it->data;
		if (res == true) {
			pl->level += 1;
			tcp_conn_printf(pl->conn, "Current level: %u\n", pl->level);
		}
		else
			tcp_conn_printf(pl->conn, "ko\n");
	}
	return (true);
}

bool zpy_srv_cmd_incantation(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	zpy_srv_cmd_t *c = malloc(sizeof(*c));

	if (!c)
		return (false);
	c->args = strdup(args);
	c->handler = &zpy_srv_incantation_step;
	c->countdown = 300;
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	if (zpy_srv_is_incantation_ok(client) == true)
		tcp_conn_printf(conn, "Elevation underway\n");
	else
		tcp_conn_printf(conn, "ko\n");
	list_push_back(client->player->cmd_queue, c);
	return (true);
}
