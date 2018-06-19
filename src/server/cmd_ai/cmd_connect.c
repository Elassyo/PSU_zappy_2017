/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Connect_nbr command
*/

#include <stdio.h>

#include "zappy_server.h"

bool zpy_srv_cmd_connect(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	printf("tg calr\n");
	unsigned short teamnumber = client->player->team;
	list_node_t *teams = client->server->teams->head;
	zpy_srv_team_t *data;

	for (unsigned short i = 0; i < teamnumber; i++)
		teams = teams->next;
	data = teams->data;
	tcp_conn_printf(conn, "%d\n", (data->max_players - data->players->len));
	return (true);
}
