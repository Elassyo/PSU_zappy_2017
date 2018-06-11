/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy server header
*/

#if !defined (ZAPPY_SERVER_H_)
	#define ZAPPY_SERVER_H_

	#include "tcp.h"
	#include "zappy.h"

typedef struct zpy_srv {
	tcp_server_t tcp;
} zpy_srv_t;

typedef struct zpy_srv_client {
	zpy_srv_t *server;
} zpy_srv_client_t;

typedef struct zpy_srv_cmd {
	char const *str;
	bool (*handler)(tcp_conn_t*, zpy_srv_client_t*, char const*);
} zpy_srv_cmd_t;

void zpy_srv_conn_on_connect(tcp_conn_t *conn, void *args);
void zpy_srv_conn_on_disconnect(tcp_conn_t *conn);
bool zpy_srv_conn_on_data(tcp_conn_t *conn);

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn,
	char const *cmd, char const *args);

bool cmd_forward(tcp_conn_t *conn, zpy_srv_client_t *cmd,
	char const *args);
bool cmd_left(tcp_conn_t *conn, zpy_srv_client_t *cmd,
	char const *args);
bool cmd_right(tcp_conn_t *conn, zpy_srv_client_t *cmd,
	char const *args);

#endif /* !defined (ZAPPY_SERVER_H_) */
