/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SST graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_sst(tcp_conn_t *conn, va_list args __attribute__ ((unused)))
{
	zpy_srv_client_t *client = conn->data;

	client->server->freq = va_arg(args, unsigned int);
	client->server->tcp.tickrate = 1.0 / client->server->freq;
	tcp_conn_printf(conn, "sst %u\n", client->server->freq);
}
