/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction (local-end info routines)
*/

#include <string.h>

#include "tcp.h"

uint32_t tcp_sock_addr(tcp_sock_t *sock)
{
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);

	getsockname(sock->fd, (struct sockaddr*)&sin, &sin_len);
	return (ntohl(sin.sin_addr.s_addr));
}

uint16_t tcp_sock_port(tcp_sock_t *sock)
{
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);

	getsockname(sock->fd, (struct sockaddr*)&sin, &sin_len);
	return (ntohs(sin.sin_port));
}

void tcp_sock_host(tcp_sock_t *sock, char *buf, size_t bufsz)
{
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);

	getsockname(sock->fd, (struct sockaddr *)&sin, &sin_len);
	if (getnameinfo((struct sockaddr *)&sin, sin_len,
		buf, bufsz, NULL, 0, NI_NAMEREQD | NI_NOFQDN) == 0)
		return;
	strncpy(buf, inet_ntoa(sock->sin.sin_addr), bufsz);
}
