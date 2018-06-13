/*
** EPITECH PROJECT, 2018
** cmd movement
** File description:
** cmd movement
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_forward(tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move forward\n");
	//Move le iencli de 1 dans sa direction
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}

bool cmd_right(tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move right\n");
	//Move le iencli de 90° sur la droite
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}

bool cmd_left(tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move left\n");
	//Move le iencli de 90° sur la gauche
	cbuf_write(&conn->out, "ok\n", 3);
	return (true);
}
