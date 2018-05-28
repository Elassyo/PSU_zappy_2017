/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP server abstraction (lifetime routines)
*/

#include <stdlib.h>

#include "tcp.h"

bool tcp_server_start(tcp_server_t *s, uint16_t port)
{
	s->conns = NULL;
	s->conns_count = 0;
	s->pfds = NULL;
	return (tcp_sock_create(&s->sock) &&
		tcp_sock_bind(&s->sock, INADDR_ANY, port) &&
		tcp_sock_listen(&s->sock, 10));
}

void tcp_server_stop(tcp_server_t *s)
{
	while (s->conns_count > 0)
		tcp_server_conn_close(s, 0, true);
	free(s->conns);
	free(s->pfds);
	tcp_sock_close(&s->sock);
}
