/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** BCT graphic client message
*/

#include "zappy_server.h"

bool zpy_srv_grph_bct(tcp_conn_t *conn, zpy_srv_map_t *map,
	unsigned int x, unsigned int y)
{
	unsigned char q[NITEM_TYPES];
	zpy_srv_item_group_t *item_group;

	for (zpy_item_type_t i = FOOD; i < NITEM_TYPES; i++) {
		item_group = zpy_srv_map_find_item_group(map, x, y, i);
		q[i] = item_group == NULL ? 0 : item_group->amount;
	}
	tcp_conn_printf(conn, "bct %u %u %hhu %hhu %hhu %hhu %hhu %hhu %hhu\n",
		x, y, q[0], q[1], q[2], q[3], q[4], q[5], q[6]);
	return (true);
}
