/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Graphic client
*/

#include "zappy_server.h"

bool zpy_srv_grph_add(zpy_srv_t *server, tcp_conn_t *conn)
{
	list_push_back(server->graphic_clients, conn);
	return (true);
}

void zpy_srv_grph_remove(zpy_srv_t *server, tcp_conn_t *conn)
{
	list_remove(server->graphic_clients,
		list_find(server->graphic_clients, conn, NULL));
}

void zpy_srv_grph_printf(zpy_srv_t *server, const char *fmt, ...)
{
	list_node_t *node;
	va_list args;
	va_list args_copy;

	va_start(args, fmt);
	node = server->graphic_clients->head;
	while (node != NULL) {
		va_copy(args_copy, args);
		tcp_conn_vprintf(node->data, fmt, args_copy);
		va_end(args_copy);
		node = node->next;
	}
	va_end(args);
}
