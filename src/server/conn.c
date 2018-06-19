/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** TCP connections events callbacks
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

void zpy_srv_conn_on_connect(tcp_conn_t *conn, void *args)
{
	zpy_srv_client_t *client;

	client = malloc(sizeof(*client));
	memset(client, 0, sizeof(*client));
	client->server = args;
	conn->data = client;
	tcp_conn_printf(conn, "WELCOME\n");
}

void zpy_srv_conn_on_disconnect(tcp_conn_t *conn)
{
	zpy_srv_client_t *client = conn->data;

	if (client->type == CLIENT_AI) {
		zpy_srv_player_remove(client->server, client->player);
		tcp_conn_printf(conn, "dead\n");
	}
	free(client);
}

static bool zpy_srv_conn_calc_tick(tcp_conn_t *conn, zpy_srv_client_t *client)
{
	struct timespec ts;
	double delta;

	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	delta = (ts.tv_sec + (double)ts.tv_nsec / 1000000000) -
		(client->last_tick.tv_sec +
			(double)client->last_tick.tv_nsec / 1000000000);
	while (delta > 1.0 / client->server->freq) {
		if (!zpy_srv_player_tick(conn, client->player))
			return (false);
		client->last_tick = ts;
		delta -= 1.0 / client->server->freq;
	}
	return (true);
}

static bool zpy_srv_conn_do_command(tcp_conn_t *conn, zpy_srv_client_t *client,
	char *msg)
{
	size_t len;
	char *args;

	if (client->type == CLIENT_UNKNOWN) {
		if (!zpy_srv_teams_join(conn, client, msg))
			return (false);
		clock_gettime(CLOCK_MONOTONIC_RAW, &client->last_tick);
		return (true);
	}
	len = strcspn(msg, " ");
	args = msg + len;
	if (*args)
		args++;
	msg[len] = 0;
	return (zpy_srv_dispatch_cmd(conn, client, msg, args));
}

bool zpy_srv_conn_on_tick(tcp_conn_t *conn)
{
	zpy_srv_client_t *client = conn->data;
	char buf[512];
	ssize_t ssz;

	if (client->type == CLIENT_AI && !zpy_srv_conn_calc_tick(conn, client))
		return (false);
	while (client->type != CLIENT_AI ||
		client->player->cmd_queue->len < 10) {
		ssz = tcp_conn_getline(conn, buf, 512, '\n');
		if (ssz <= 0)
			return (ssz == 0);
		if (!zpy_srv_conn_do_command(conn, client, buf))
			return (false);
	}
	return (true);
}
