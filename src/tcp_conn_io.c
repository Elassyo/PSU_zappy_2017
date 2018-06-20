/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections (low level IO routines)
*/

#include <stdio.h>

#include "tcp.h"

bool tcp_conn_fetch(tcp_conn_t *conn)
{
	char buf[1024];
	ssize_t ssz;

	ssz = tcp_sock_recv(&conn->sock, buf,
		min(1024, cbuf_free_bytes(&conn->in)));
	if (ssz <= 0)
		return (false);
	cbuf_write(&conn->in, buf, ssz);
	return (true);
}

bool tcp_conn_flush(tcp_conn_t *conn)
{
	char buf[1024];
	size_t sz;
	ssize_t ssz;

	while (cbuf_used_bytes(&conn->out) > 0) {
		sz = cbuf_peek(&conn->out, buf,
			min(cbuf_used_bytes(&conn->out), 1024));
		ssz = tcp_sock_send(&conn->sock, buf, sz);
		if (ssz <= 0)
			return (false);
		cbuf_read(&conn->out, NULL, ssz);
	}
	return (true);
}

size_t tcp_conn_read(tcp_conn_t *conn, void *buf, size_t n)
{
	if (conn->block && cbuf_used_bytes(&conn->in) < n)
		tcp_conn_fetch(conn);
	return (cbuf_read(&conn->in, buf, n));
}

size_t tcp_conn_peek(tcp_conn_t *conn, void *buf, size_t n)
{
	if (conn->block && cbuf_used_bytes(&conn->in) < n)
		tcp_conn_fetch(conn);
	return (cbuf_peek(&conn->in, buf, n));
}

size_t tcp_conn_write(tcp_conn_t *conn, void const *buf, size_t n)
{
	size_t sz;

	sz = cbuf_write(&conn->out, buf, n);
	if (conn->block)
		tcp_conn_flush(conn);
	return (sz);
}
