/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP server abstraction (Client connections routines)
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tcp.h"

void tcp_server_conn_accept(tcp_server_t *s)
{
	tcp_conn_t *conn;

	s->conns = realloc(s->conns, (s->conns_count + 1) * sizeof(*s->conns));
	conn = malloc(sizeof(*s->conns[s->conns_count]));
	tcp_sock_accept(&s->sock, &conn->sock);
	cbuf_create(&conn->in, 4096);
	cbuf_create(&conn->out, 8192);
	s->on_connect(conn, s->on_connect_args);
	s->conns[s->conns_count++] = conn;
}

void tcp_server_conn_close(tcp_server_t *s, size_t i, bool flush)
{
	char buf[1024];
	size_t sz;
	ssize_t ssz;

	s->on_disconnect(s->conns[i]);
	while (flush && cbuf_used_bytes(&s->conns[i]->out) > 0) {
		sz = cbuf_peek(&s->conns[i]->out, buf,
			min(cbuf_used_bytes(&s->conns[i]->out), 1024));
		ssz = tcp_sock_send(&s->conns[i]->sock, buf, sz);
		if (ssz <= 0)
			break;
		cbuf_read(&s->conns[i]->out, NULL, ssz);
	}
	tcp_sock_close(&s->conns[i]->sock);
	cbuf_destroy(&s->conns[i]->in);
	cbuf_destroy(&s->conns[i]->out);
	free(s->conns[i]);
	memmove(s->conns + i, s->conns + i + 1,
		(s->conns_count - i - 1) * sizeof(*s->conns));
	s->conns = realloc(s->conns, --s->conns_count * sizeof(*s->conns));
}
