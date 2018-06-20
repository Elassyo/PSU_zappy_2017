/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TNA graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_tna(tcp_conn_t *conn, va_list args __attribute__ ((unused)))
{
	zpy_srv_client_t *client = conn->data;
	zpy_srv_team_t *team;
	list_node_t *node;

	node = client->server->teams->head;
	while (node != NULL) {
		team = node->data;
		tcp_conn_printf(conn, "tna %s\n", team->name);
		node = node->next;
	}
}
