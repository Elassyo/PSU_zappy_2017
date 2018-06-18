/*
** EPITECH PROJECT, 2018
** cmd look
** File description:
** cmd look
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_look(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("look around\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
