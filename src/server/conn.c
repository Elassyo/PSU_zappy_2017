/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections events callbacks
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

void zpy_srv_conn_on_connect(tcp_server_conn_t *conn, void *args)
{
	zpy_srv_client_t *client;

	client = malloc(sizeof(*client));
	memset(client, 0, sizeof(*client));
	client->server = args;
	conn->data = client;
}

void zpy_srv_conn_on_disconnect(tcp_server_conn_t *conn)
{
	zpy_srv_client_t *client = conn->data;

	free(client);
}

static bool zpy_srv_conn_do_command(tcp_server_conn_t *conn, char *msg)
{
	size_t len;
	char *args;

	len = strcspn(msg, " ");
	args = msg + len;
	if (*args)
		args++;
	msg[len] = 0;
	return (zpy_srv_dispatch_cmd(conn, msg, args));
}

bool zpy_srv_conn_on_data(tcp_server_conn_t *conn)
{
	char buf[512];
	char *end;
	size_t sz;

	while (cbuf_free_bytes(&conn->out) >= 512) {
		sz = min(512, cbuf_used_bytes(&conn->in));
		cbuf_peek(&conn->in, buf, sz);
		end = memchr(buf, '\n', sz);
		if (end == NULL)
			return (sz != 512);
		*end = '\0';
		cbuf_read(&conn->in, NULL, end - buf + 1);
		if (!zpy_srv_conn_do_command(conn, buf))
			return (false);
	}
	return (true);
}
