/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MSZ graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_msz(tcp_conn_t *conn, va_list args)
{
	zpy_srv_map_t *map = va_arg(args, zpy_srv_map_t*);

	tcp_conn_printf(conn, "msz %u %u\n", map->width, map->height);
}
