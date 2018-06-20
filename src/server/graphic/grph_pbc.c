/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PBC graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pbc(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "pbc %u %s\n",
		va_arg(args, zpy_srv_player_t*)->id,
		va_arg(args, char const *));
}
