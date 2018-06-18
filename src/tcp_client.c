/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP client abstraction
*/

#include <stddef.h>
#include <stdio.h>

#include "tcp.h"

bool tcp_client_connect(tcp_client_t *c, char const *host, uint16_t port)
{
	struct hostent *he;

	he = gethostbyname(host);
	if (he == NULL || he->h_addr == NULL)
		return (false);
	if (!tcp_client_conn_connect(c,
		ntohl(((struct in_addr*)he->h_addr)->s_addr), port))
		return (false);

	tcp_client_conn_close(c, true);
	return (true);
}
