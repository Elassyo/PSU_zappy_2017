/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP server abstraction (serving routines)
*/

#include <assert.h>
#include <signal.h>
#include <stdlib.h>

#include "tcp.h"

static bool g_running;

static void tcp_server_sighandler(int signal)
{
	if (signal == SIGINT)
		g_running = false;
}

static bool tcp_server_handle_poll_io(tcp_server_t *s, tcp_server_conn_t *c,
	short revents)
{
	char buf[1024];
	size_t sz;
	ssize_t ssz;

	if (revents & POLLIN) {
		ssz = tcp_sock_recv(&c->sock, buf,
			min(cbuf_free_bytes(&c->in), 1024));
		if (ssz <= 0)
			return (false);
		cbuf_write(&c->in, buf, ssz);
	} else if (revents & POLLOUT) {
		sz = cbuf_peek(&c->out, buf,
			min(cbuf_used_bytes(&c->out), 1024));
		ssz = tcp_sock_send(&c->sock, buf, sz);
		if (ssz <= 0)
			return (false);
		cbuf_read(&c->out, NULL, ssz);
	}
	return (s->on_data(c));
}

static void tcp_server_handle_poll_conn(tcp_server_t *s)
{
	size_t pfds_idx = 1;

	for (size_t i = 0; i < s->conns_count; i++) {
		if (tcp_server_handle_poll_io(s, s->conns[i],
			s->pfds[pfds_idx++].revents))
			continue;
		tcp_server_conn_close(s, i--, false);
	}
	if (s->pfds[0].revents & POLLIN)
		tcp_server_conn_accept(s);
}

void tcp_server_serve(tcp_server_t *s)
{
	size_t conns_count_sv = s->conns_count;

	if (s->pfds == NULL)
		s->pfds = malloc((s->conns_count + 1) * sizeof(*s->pfds));
	assert(s->pfds != NULL);
	s->pfds[0].fd = s->sock.fd;
	s->pfds[0].events = POLLIN;
	for (size_t i = 0; i < s->conns_count; i++) {
		s->pfds[i + 1].fd = s->conns[i]->sock.fd;
		s->pfds[i + 1].events = POLLIN;
		if (cbuf_used_bytes(&s->conns[i]->out) != 0)
			s->pfds[i + 1].events |= POLLOUT;
	}
	if (poll(s->pfds, s->conns_count + 1, -1) < 0)
		return;
	tcp_server_handle_poll_conn(s);
	if (s->conns_count != conns_count_sv) {
		free(s->pfds);
		s->pfds = NULL;
	}
}

void tcp_server_serve_forever(tcp_server_t *server)
{
	struct sigaction sa;
	struct sigaction sa_original;

	g_running = true;
	sa.sa_handler = tcp_server_sighandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &sa_original);
	while (g_running)
		tcp_server_serve(server);
	sigaction(SIGINT, &sa_original, NULL);
}
