/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TNA graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_tna(tcp_conn_t *conn, va_list args)
{
	list_t *teams = va_arg(args, list_t*);
	list_node_t *node;
	zpy_srv_team_t *team;

	node = teams->head;
	while (node != NULL) {
		team = node->data;
		tcp_conn_printf(conn, "tna %s\n", team->name);
		node = node->next;
	}
}
