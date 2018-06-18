/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP socket abstraction (IO routines)
*/

#include <unistd.h>

#include "tcp.h"

ssize_t tcp_sock_recv(tcp_sock_t *sock, void *buf, size_t len)
{
	return (read(sock->fd, buf, len));
}

ssize_t tcp_sock_send(tcp_sock_t *sock, void const *buf, size_t len)
{
	return (write(sock->fd, buf, len));
}
