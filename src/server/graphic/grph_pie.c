/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PIE graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pie(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "pie %u %u %u\n",
		va_arg(args, unsigned int), va_arg(args, unsigned int),
		va_arg(args, int) ? 1 : 0);
}
