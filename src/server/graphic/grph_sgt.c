/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SGT graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_sgt(tcp_conn_t *conn, va_list args __attribute__ ((unused)))
{
	zpy_srv_client_t *client = conn->data;

	tcp_conn_printf(conn, "sgt %u\n", client->server->freq);
}
