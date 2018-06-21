/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ENW graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_enw(tcp_conn_t *conn, va_list args)
{
	zpy_srv_egg_t *egg = va_arg(args, zpy_srv_egg_t*);

	tcp_conn_printf(conn, "enw %u %u %u %u\n", egg->id,
		egg->parent_id, egg->x, egg->y);
}
