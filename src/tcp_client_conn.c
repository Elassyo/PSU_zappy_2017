/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP client abstraction (connections routines)
*/

#include "tcp.h"
/*
bool tcp_client_conn_connect(tcp_client_t *c, uint32_t addr, uint16_t port)
{
	if (!(tcp_sock_create(&c->conn.sock) &&
		!tcp_sock_connect(&c->conn.sock, addr, port)))
		return (false);
	cbuf_create(&c->conn.in, 8192);
	cbuf_create(&c->conn.out, 4096);
	c->on_connect(&c->conn, c->on_connect_args);
	return (true);
}

void tcp_client_conn_close(tcp_client_t *c, bool flush)
{
	char buf[1024];
	size_t sz;
	ssize_t ssz;

	c->on_disconnect(&c->conn);
	while (flush && cbuf_used_bytes(&c->conn.out) > 0) {
		sz = cbuf_peek(&c->conn.out, buf,
			min(cbuf_used_bytes(&c->conn.out), 1024));
		ssz = tcp_sock_send(&c->conn.sock, buf, sz);
		if (ssz <= 0)
			break;
		cbuf_read(&c->conn.out, NULL, ssz);
	}
	tcp_sock_close(&c->conn.sock);
	cbuf_destroy(&c->conn.in);
	cbuf_destroy(&c->conn.out);
}
*/
