/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections (high level IO routines)
*/

#include <stdarg.h>
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
	*end = '\0';
	tcp_conn_read(conn, NULL, end - buf + 1);
	return (sz);
}

size_t tcp_conn_printf(tcp_conn_t *conn, char const *fmt, ...)
{
	char buf[conn->out.size];
	va_list va;
	size_t len;

	va_start(va, fmt);
	len = vsnprintf(buf, conn->out.size, fmt, va);
	va_end(va);
	return (tcp_conn_write(conn, buf, len));
}
