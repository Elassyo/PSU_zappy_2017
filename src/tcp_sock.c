/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction
*/

#include <unistd.h>

#include "tcp.h"

bool tcp_sock_create(tcp_sock_t *sock)
{
	sock->fd = socket(AF_INET, SOCK_STREAM, 0);
	return (sock->fd >= 0);
}

void tcp_sock_close(tcp_sock_t *sock)
{
	if (sock->fd >= 0)
		close(sock->fd);
	sock->fd = -1;
}
