/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MCT graphic client message
*/

#include "zappy_server.h"

bool zpy_srv_grph_mct(tcp_conn_t *conn, zpy_srv_map_t *map)
{
	for (unsigned int y = 0; y < map->height; y++) {
		for (unsigned int x = 0; x < map->width; x++)
			zpy_srv_grph_bct(conn, map, x, y);
		tcp_conn_flush(conn);
	}
	return (true);
}
