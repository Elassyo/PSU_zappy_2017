/*
** EPITECH PROJECT, 2018
** cmd connect
** File description:
** cmd connect
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_connect(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
{
	printf("connect nbr\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
