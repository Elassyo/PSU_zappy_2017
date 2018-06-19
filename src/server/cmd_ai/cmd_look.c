/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Look command
*/

#include <stdio.h>

#include "zappy_server.h"

bool zpy_srv_cmd_look(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args)
{
	(void)conn, (void)client, (void)args;
	printf("Look TODO\n");
	return (true);
}
