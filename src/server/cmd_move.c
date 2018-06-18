/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Movement commands
*/

#include <stdio.h>

#include "zappy_server.h"

bool cmd_forward(tcp_conn_t *conn __attribute__((unused)),
	zpy_srv_client_t *client __attribute__((unused)),
	char const *cmd  __attribute__((unused)))
{
	printf("Move forward\n");
	//Move le iencli de 1 dans sa direction
	return (true);
}

bool cmd_left(tcp_conn_t *conn __attribute__((unused)),
	zpy_srv_client_t *client __attribute__((unused)),
	char const *cmd  __attribute__((unused)))
{
	printf("Move left\n");
	//Move le iencli de 90° sur la gauche
	return (true);
}

bool cmd_right(tcp_conn_t *conn __attribute__((unused)),
	zpy_srv_client_t *client __attribute__((unused)),
	char const *cmd  __attribute__((unused)))
{
	printf("Move right\n");
	//Move le iencli de 90° sur la droite
	return (true);
}
