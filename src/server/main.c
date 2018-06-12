/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy server main
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "zappy_server.h"
#include "args.h"

static int usage(char const *progname, int ret)
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

static int zpy_server(char const *progname, uint16_t port)
{
	zpy_srv_t server;

	memset(&server, 0, sizeof(server));
	server.tcp.on_connect_args = &server;
	server.tcp.on_connect = &zpy_srv_conn_on_connect;
	server.tcp.on_disconnect = &zpy_srv_conn_on_disconnect;
	server.tcp.on_data = &zpy_srv_conn_on_data;
	if (!tcp_server_start(&server.tcp, port)) {
		fprintf(stderr, "%s: failed to start server: %s\n",
			progname, strerror(errno));
		return (84);
	}
	tcp_server_serve_forever(&server.tcp);
	tcp_server_stop(&server.tcp);
	return (0);
}

/* TODO: main + parsing args */
int main(int argc, char const **argv)
{
	args_t args;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-help") == 0)
			return (usage(argv[0], 0));
	}
	if (argc < 13) {
		fprintf(stderr, "%s: not enough arguments\n", argv[0]);
		return (usage(argv[0], 84));
	}
	if (parse_args(&args, argc, argv) == -1) {
		fprintf(stderr, "error with one of the arguments\n");
		return (usage(argv[0], 84));
	}
	return (0);
}
