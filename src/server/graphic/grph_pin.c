/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** PIN graphic client message
*/

#include "zappy_server.h"

void zpy_srv_grph_pin(tcp_conn_t *conn, va_list args)
{
	zpy_srv_player_t *player = va_arg(args, zpy_srv_player_t*);

	tcp_conn_printf(conn,
		"pin %u %u %u %hhu %hhu %hhu %hhu %hhu %hhu %hhu\n",
		player->id, player->x, player->y,
		player->inventory[0], player->inventory[1],
		player->inventory[2], player->inventory[3],
		player->inventory[4], player->inventory[5],
		player->inventory[6]);
}
