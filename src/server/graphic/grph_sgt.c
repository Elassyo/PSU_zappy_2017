/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SGT graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_sgt(tcp_conn_t *conn, va_list args)
{
	zpy_srv_t *server = va_arg(args, zpy_srv_t*);

	tcp_conn_printf(conn, "sgt %u\n", server->freq);
}
