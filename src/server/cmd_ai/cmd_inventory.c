/*
** EPITECH PROJECT, 2018
** cmd inventory
** File description:
** cmd inventory
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_inventory(tcp_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
{
	printf("inventory\n");
	//TODO
	cbuf_write(&conn->out, "todo\n", 5);
	return (true);
}
