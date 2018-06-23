/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PIC graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pic(tcp_conn_t *conn, va_list args)
{
	list_t *players;
	list_node_t *node;
	zpy_srv_player_t *player;

	players = zpy_srv_incantation_players(va_arg(args, zpy_srv_client_t*));
	node = players->head;
	player = node->data;
	tcp_conn_printf(conn, "pic %u %u %u",
		player->x, player->y, player->level);
	while (node != NULL) {
		player = node->data;
		tcp_conn_printf(conn, " %u", player->id);
		node = node->next;
	}
	list_destroy(players);
}
