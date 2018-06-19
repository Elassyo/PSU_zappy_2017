/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy server main
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zappy_server.h"

static int zpy_srv_usage(char const *progname, int ret)
{
	printf("USAGE: %s -p port -x width -y height -n name1 name2 ... -c "
		"clientsNb -f freq\n", progname);
	puts("\tport\t\tis the port number");
	puts("\twidth\t\tis width of the world");
	puts("\theight\t\tis height of the world");
	puts("\tnameX\t\tis the name of the team X");
	puts("\tclientsNb\tis the number of authorized clients per team");
	puts("\tfreq\t\tis the reciprocal of time unit per execution of "
		"actions");
	return (ret);
}

static int zpy_srv_run(zpy_srv_t *server, char const *progname)
{
	if (!zpy_srv_map_init(&server->map) || !zpy_srv_teams_init(server))
		return (84);
	server->tcp.on_connect_args = server;
	server->tcp.on_connect = &zpy_srv_conn_on_connect;
	server->tcp.on_disconnect = &zpy_srv_conn_on_disconnect;
	server->tcp.on_tick = &zpy_srv_conn_on_tick;
	server->tcp.tickrate = 1.0 / server->freq;
	if (!tcp_server_start(&server->tcp, server->port)) {
		fprintf(stderr, "%s: failed to start server: %s\n",
			progname, strerror(errno));
		return (84);
	}
	tcp_server_serve_forever(&server->tcp);
	tcp_server_stop(&server->tcp);
	zpy_srv_map_cleanup(&server->map);
	return (0);
}

int main(int argc, char **argv)
{
	int ret;
	zpy_srv_t server;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-help") == 0)
			return (zpy_srv_usage(argv[0], 0));
	}
	memset(&server, 0, sizeof(server));
	server.freq = 100;
	server.teams = list_create(true);
	if (!zpy_srv_args_parse(&server, argc, argv)) {
		fprintf(stderr, "%s: invalid or missing argument\n", argv[0]);
		return (zpy_srv_usage(argv[0], 84));
	}
	srand(time(NULL));
	ret = zpy_srv_run(&server, argv[0]);
	zpy_srv_teams_cleanup(server.teams);
	return (ret);
}
