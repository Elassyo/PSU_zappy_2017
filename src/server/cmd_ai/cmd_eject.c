/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Eject command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_eject(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	(void)client;
	if (strcmp(args, "") != 0) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	printf("Eject TODO\n");
	return (true);
}
