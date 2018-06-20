/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** SST command
*/

#include <stdio.h>
#include <string.h>

#include "zappy_server.h"

bool zpy_srv_cmd_sst(tcp_conn_t *conn,
	zpy_srv_client_t *client __attribute__ ((unused)), char const *args)
{
	unsigned int freq;
	size_t rd;

	if (sscanf(args, "%u%zn", &freq, &rd) != 2 || rd != strlen(args) ||
		freq == 0) {
		tcp_conn_printf(conn, "sbp\n");
		return (true);
	}
	zpy_srv_grph_send(conn, &zpy_srv_grph_sst, freq);
	return (true);
}
