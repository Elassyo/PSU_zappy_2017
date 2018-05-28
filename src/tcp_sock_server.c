/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction (server routines)
*/

#include <string.h>

#include "tcp.h"

bool tcp_sock_bind(tcp_sock_t *sock, uint32_t addr, uint16_t port)
{
	memset(&sock->sin, 0, sizeof(sock->sin));
	sock->sin.sin_family = AF_INET;
	sock->sin.sin_addr.s_addr = htonl(addr);
	sock->sin.sin_port = htons(port);
	return (bind(sock->fd,
		(struct sockaddr*)&sock->sin, sizeof(sock->sin)) == 0);
}

bool tcp_sock_listen(tcp_sock_t *sock, int backlog)
{
	return (listen(sock->fd, backlog) == 0);
}

bool tcp_sock_accept(tcp_sock_t *sock, tcp_sock_t *conn)
{
	socklen_t sin_len = sizeof(conn->sin);

	conn->fd = accept(sock->fd,
		(struct sockaddr*)&conn->sin, &sin_len);
	return (conn->fd >= 0 && sin_len == sizeof(conn->sin));
}
