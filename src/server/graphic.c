/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Graphic client
*/

#include "zappy_server.h"

bool zpy_srv_grph_add(zpy_srv_t *server, tcp_conn_t *conn)
{
	zpy_srv_client_t *client;
	list_node_t *node;

	client = conn->data;
	list_push_back(server->graphic_clients, conn);
	zpy_srv_grph_send(conn, &zpy_srv_grph_msz, &client->server->map);
	zpy_srv_grph_send(conn, &zpy_srv_grph_sgt, client->server);
	zpy_srv_grph_send(conn, &zpy_srv_grph_mct, &client->server->map);
	zpy_srv_grph_send(conn, &zpy_srv_grph_tna, client->server->teams);
	node = client->server->map.players->head;
	while (node != NULL) {
		zpy_srv_grph_send(conn, &zpy_srv_grph_pnw, conn->data);
		node = node->next;
	}
	return (true);
}

void zpy_srv_grph_remove(zpy_srv_t *server, tcp_conn_t *conn)
{
	list_remove(server->graphic_clients,
		list_find(server->graphic_clients, conn, NULL));
}

void zpy_srv_grph_send(tcp_conn_t *conn,
	void (*handler)(tcp_conn_t *, va_list), ...)
{
	va_list args;

	va_start(args, handler);
	handler(conn, args);
	va_end(args);
}

void zpy_srv_grph_sendall(zpy_srv_t *server,
	void (*handler)(tcp_conn_t *, va_list), ...)
{
	list_node_t *node;
	va_list args;
	va_list args_copy;

	va_start(args, handler);
	node = server->graphic_clients->head;
	while (node != NULL) {
		va_copy(args_copy, args);
		handler(node->data, args_copy);
		va_end(args_copy);
		node = node->next;
	}
	va_end(args);
}
