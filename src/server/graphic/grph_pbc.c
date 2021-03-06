/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PBC graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pbc(tcp_conn_t *conn, va_list args)
{
	zpy_srv_player_t *player = va_arg(args, zpy_srv_player_t*);
	char const *msg = va_arg(args, char const *);

	tcp_conn_printf(conn, "pbc %u %s\n", player->id, msg);
}
