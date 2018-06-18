/*
** EPITECH PROJECT, 2018
** cmd take
** File description:
** cmd take
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_take(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("take nbr\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
