/*
** EPITECH PROJECT, 2018
** cmd incantation
** File description:
** cmd incantation
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_incantation(tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("incantation nbr\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}