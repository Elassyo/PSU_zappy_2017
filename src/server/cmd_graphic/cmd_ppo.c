/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PPO command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_ppo(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	unsigned int id;
	size_t rd;
	zpy_srv_player_t *player;

	if (sscanf(args, "%u%zn", &id, &rd) != 1 || rd != strlen(args)) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	player = zpy_srv_player_find(&client->server->map, id);
	if (player == NULL) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	zpy_srv_grph_send(conn, &zpy_srv_grph_ppo, player);
	return (true);
}
