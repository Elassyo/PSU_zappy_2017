/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections
*/

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
