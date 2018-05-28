/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction (remote-end info routines)
*/

#include <string.h>

#include "tcp.h"

uint32_t tcp_sock_raddr(tcp_sock_t *sock)
{
	return (ntohl(sock->sin.sin_addr.s_addr));
}

uint16_t tcp_sock_rport(tcp_sock_t *sock)
{
	return (ntohs(sock->sin.sin_port));
}

void tcp_sock_rhost(tcp_sock_t *sock, char *buf, size_t bufsz)
{
	if (getnameinfo((struct sockaddr *)&sock->sin, sizeof(sock->sin),
		buf, bufsz, NULL, 0, NI_NAMEREQD | NI_NOFQDN) == 0)
		return;
	strncpy(buf, inet_ntoa(sock->sin.sin_addr), bufsz);
}
