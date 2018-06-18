/*
** EPITECH PROJECT, 2018
** cmd eject
** File description:
** cmd eject
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_eject(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("eject nbr\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
