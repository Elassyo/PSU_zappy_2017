/*
** EPITECH PROJECT, 2018
** cmd movement
** File description:
** cmd movement
*/

#include <stdio.h>
#include "zappy_server.h"

bool cmd_forward(__attribute__((unused))tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move forward\n");
	//Move le iencli de 1 dans sa direction
	return (true);
}

bool cmd_right(__attribute__((unused))tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move right\n");
	//Move le iencli de 90° sur la droite
	return (true);
}

bool cmd_left(__attribute__((unused))tcp_server_conn_t *conn,
		__attribute__((unused))zpy_srv_client_t *iencli,
		__attribute__((unused))char const *cmd)
{
	printf("Move left\n");
	//Move le iencli de 90° sur la gauche
	return (true);
}
