/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PPO graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pnw(tcp_conn_t *conn, va_list args)
{
	zpy_srv_player_t *player = va_arg(args, zpy_srv_player_t*);
	zpy_srv_client_t *client = conn->data;
	zpy_srv_team_t *team;

	team = list_get(client->server->teams, player->team);
	tcp_conn_printf(conn, "pnw %u %u %u %hhu %hhu %s\n", player->id,
		player->x, player->y, player->direction + 1, player->level,
		team->name);
}
