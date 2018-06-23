/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PIE graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pie(tcp_conn_t *conn, va_list args)
{
	unsigned int x = va_arg(args, unsigned int);
	unsigned int y = va_arg(args, unsigned int);
	int res = va_arg(args, int);

	tcp_conn_printf(conn, "pie %u %u %u\n", x, y, res ? 1 : 0);
}
