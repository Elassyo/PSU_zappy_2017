/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MSZ graphic client message
*/

#include "zappy_server.h"

bool zpy_srv_grph_msz(tcp_conn_t *conn, zpy_srv_map_t *map)
{
	tcp_conn_printf(conn, "msz %u %u\n", map->width, map->height);
	return (true);
}
