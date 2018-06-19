/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP server abstraction (connections routines)
*/

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tcp.h"

bool tcp_server_conn_accept(tcp_server_t *s)
{
	tcp_conn_t *conn;

	s->conns = realloc(s->conns, (s->conns_count + 1) * sizeof(*s->conns));
	assert(s->conns != NULL);
	conn = malloc(sizeof(*s->conns[s->conns_count]));
	if (conn == NULL)
		return (false);
	if (!tcp_sock_accept(&s->sock, &conn->sock))
		return (false);
	if (!cbuf_create(&conn->in, 4096) || !cbuf_create(&conn->out, 8192))
		return (false);
	conn->block = false;
	s->on_connect(conn, s->on_connect_args);
	s->conns[s->conns_count++] = conn;
	return (true);
}

void tcp_server_conn_close(tcp_server_t *s, size_t i, bool flush)
{
	s->on_disconnect(s->conns[i]);
	if (flush)
		tcp_conn_flush(s->conns[i]);
	tcp_sock_close(&s->conns[i]->sock);
	cbuf_destroy(&s->conns[i]->in);
	cbuf_destroy(&s->conns[i]->out);
	free(s->conns[i]);
	memmove(s->conns + i, s->conns + i + 1,
		(s->conns_count - i - 1) * sizeof(*s->conns));
	s->conns = realloc(s->conns, --s->conns_count * sizeof(*s->conns));
	assert(s->conns_count == 0 || s->conns != NULL);
}
