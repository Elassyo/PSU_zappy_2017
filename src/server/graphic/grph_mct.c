/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** MCT graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_mct(tcp_conn_t *conn, va_list args __attribute__ ((unused)))
{
	zpy_srv_client_t *client = conn->data;
	zpy_srv_map_t *map = &client->server->map;

	for (unsigned int y = 0; y < map->height; y++) {
		for (unsigned int x = 0; x < map->width; x++)
			zpy_srv_grph_send(conn, &zpy_srv_grph_bct, x, y);
		tcp_conn_flush(conn);
	}
}
