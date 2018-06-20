/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SST graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_sst(tcp_conn_t *conn, va_list args)
{
	zpy_srv_t *server = va_arg(args, zpy_srv_t*);

	server->freq = va_arg(args, unsigned int);
	server->tcp.tickrate = 1.0 / server->freq;
	tcp_conn_printf(conn, "sst %u\n", server->freq);
}
