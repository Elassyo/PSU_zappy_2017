/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PEX graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pex(tcp_conn_t *conn, va_list args)
{
	zpy_srv_player_t *player = va_arg(args, zpy_srv_player_t*);

	tcp_conn_printf(conn, "pex %u\n", player->id);
}
