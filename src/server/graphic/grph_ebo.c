/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** EBO graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_ebo(tcp_conn_t *conn, va_list args)
{
	tcp_conn_printf(conn, "ebo %u\n",
		va_arg(args, zpy_srv_egg_t*)->id);
}