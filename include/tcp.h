/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** TCP abstraction
*/

#if !defined (TCP_H_)
	#define TCP_H_

	#include <netdb.h>
	#include <poll.h>
	#include <stdbool.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <sys/socket.h>

	#include "cbuf.h"

	#ifdef __cplusplus
extern "C" {
	#endif

typedef struct tcp_sock {
	int fd;
	struct sockaddr_in sin;
} tcp_sock_t;

typedef struct tcp_conn {
	tcp_sock_t sock;
	cbuf_t in;
	cbuf_t out;
	bool block;
	void *data;
} tcp_conn_t;

typedef struct tcp_server {
	tcp_sock_t sock;
	tcp_conn_t **conns;
	size_t conns_count;
	struct pollfd *pfds;
	void *on_connect_args;
	void (*on_connect)(tcp_conn_t *, void *);
	void (*on_disconnect)(tcp_conn_t *);
	bool (*on_tick)(tcp_conn_t *);
	double tickrate;
} tcp_server_t;

bool tcp_sock_create(tcp_sock_t *sock);
void tcp_sock_close(tcp_sock_t *sock);

uint32_t tcp_sock_addr(tcp_sock_t *sock);
uint16_t tcp_sock_port(tcp_sock_t *sock);
void tcp_sock_host(tcp_sock_t *sock, char *buf, size_t bufsz);

uint32_t tcp_sock_raddr(tcp_sock_t *sock);
uint16_t tcp_sock_rport(tcp_sock_t *sock);
void tcp_sock_rhost(tcp_sock_t *sock, char *buf, size_t bufsz);

ssize_t tcp_sock_recv(tcp_sock_t *sock, void *buf, size_t len);
size_t tcp_sock_recv_line(tcp_sock_t *sock, char *buf, size_t len,
	char const *delim);
ssize_t tcp_sock_send(tcp_sock_t *sock, void const *buf, size_t len);
bool tcp_sock_send_line(tcp_sock_t *sock, char const *buf);

bool tcp_sock_connect(tcp_sock_t *sock, uint32_t addr, uint16_t port);

bool tcp_sock_bind(tcp_sock_t *sock, uint32_t addr, uint16_t port);
bool tcp_sock_listen(tcp_sock_t *sock, int backlog);
bool tcp_sock_accept(tcp_sock_t *sock, tcp_sock_t *conn);

size_t tcp_conn_read(tcp_conn_t *conn, void *buf, size_t n);
size_t tcp_conn_peek(tcp_conn_t *conn, void *buf, size_t n);
size_t tcp_conn_write(tcp_conn_t *conn, void const *buf, size_t n);

bool tcp_server_start(tcp_server_t *s, uint16_t port);
void tcp_server_stop(tcp_server_t *s);

void tcp_server_serve(tcp_server_t *s);
void tcp_server_serve_forever(tcp_server_t *server);

bool tcp_server_conn_accept(tcp_server_t *s);
void tcp_server_conn_close(tcp_server_t *s, size_t i, bool flush);

	#ifdef __cplusplus
}
	#endif

#endif /* !defined (TCP_H_) */
