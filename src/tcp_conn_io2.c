/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections (high level IO routines)
*/

#include <stdio.h>
#include <string.h>

#include "tcp.h"

ssize_t tcp_conn_getline(tcp_conn_t *conn, char *buf, size_t n, char delim)
{
	size_t sz;
	char *end;

	sz = tcp_conn_peek(conn, buf, n);
	end = memchr(buf, delim, sz);
	if (end == NULL)
		return (sz == n ? -1 : 0);
	*(end + 1) = '\0';
	sz = end - buf + 1;
	tcp_conn_read(conn, NULL, sz);
	return (sz);
}

size_t tcp_conn_vprintf(tcp_conn_t *conn, char const *fmt, va_list args)
{
	char buf[conn->out.size];
	size_t len;

	len = vsnprintf(buf, conn->out.size, fmt, args);
	return (tcp_conn_write(conn, buf, len));
}

size_t tcp_conn_printf(tcp_conn_t *conn, char const *fmt, ...)
{
	size_t res;
	va_list args;

	va_start(args, fmt);
	res = tcp_conn_vprintf(conn, fmt, args);
	va_end(args);
	return (res);
}
