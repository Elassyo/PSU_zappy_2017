/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SEG graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_seg(tcp_conn_t *conn, va_list args)
{
	unsigned short team_nbr = va_arg(args, unsigned int);
	zpy_srv_client_t *client = conn->data;
	zpy_srv_team_t *team;

	team = list_get(client->server->teams, team_nbr);
	tcp_conn_printf(conn, "seg %s\n", team->name);
}
