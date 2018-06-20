/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PDI graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pdi(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "pdi %u\n",
		va_arg(args, zpy_srv_player_t*)->id);
}
