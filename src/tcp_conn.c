/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections
*/

#include <stdarg.h>
#include <stdio.h>

#include "tcp.h"

size_t tcp_conn_read(tcp_conn_t *conn, void *buf, size_t n)
{
	return (cbuf_read(&conn->in, buf, n));
}

size_t tcp_conn_peek(tcp_conn_t *conn, void *buf, size_t n)
{
	return (cbuf_peek(&conn->in, buf, n));
}

size_t tcp_conn_write(tcp_conn_t *conn, void const *buf, size_t n)
{
	return (cbuf_write(&conn->out, buf, n));
}

size_t tcp_conn_printf(tcp_conn_t *conn, char const *fmt, ...)
{
	char buf[512];
	va_list va;
	size_t len;

	va_start(va, fmt);
	len = vsnprintf(buf, 512, fmt, va);
	va_end(va);
	return (tcp_conn_write(conn, buf, len));
}
