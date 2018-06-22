/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PDR graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pdr(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "pdr %u %u\n",
		va_arg(args, zpy_srv_player_t*)->id,
		va_arg(args, zpy_item_type_t));
}
