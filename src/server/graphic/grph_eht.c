/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** EHT graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_eht(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "eht %u\n",
		va_arg(args, zpy_srv_egg_t*)->id);
}
