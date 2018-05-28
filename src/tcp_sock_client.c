/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction (client routines)
*/

#include <string.h>

#include "tcp.h"

bool tcp_sock_connect(tcp_sock_t *sock, uint32_t addr, uint16_t port)
{
	memset(&sock->sin, 0, sizeof(sock->sin));
	sock->sin.sin_family = AF_INET;
	sock->sin.sin_addr.s_addr = htonl(addr);
	sock->sin.sin_port = htons(port);
	return (connect(sock->fd,
		(struct sockaddr*)&sock->sin, sizeof(sock->sin)) == 0);
}
