/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP client abstraction
*/

#include "tcp.h"

bool tcp_client_connect(tcp_client_t *c, char const *host, uint16_t port)
{
	struct hostent *he;

	he = gethostbyname(host);
	if (he == NULL || he->h_addr == NULL)
		return (false);
	if (!tcp_sock_create(&c->conn.sock) ||
		!tcp_sock_connect(&c->conn.sock,
			ntohl(((struct in_addr*)he->h_addr)->s_addr), port))
		return (false);
	cbuf_create(&c->conn.in, 4096);
	cbuf_create(&c->conn.out, 8192);
	c->conn.block = true;
	return (true);

}

void tcp_client_close(tcp_client_t *c)
{
	tcp_conn_flush(&c->conn);
	tcp_sock_close(&c->conn.sock);
	cbuf_destroy(&c->conn.in);
	cbuf_destroy(&c->conn.out);

}
