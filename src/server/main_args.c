/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Args parsing
*/

#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "zappy_server.h"

static bool zpy_srv_args_parse_nbr(zpy_srv_t *server, int opt,
	char const *arg, unsigned long limit)
{
	unsigned long l;
	char *end;

	l = strtoul(arg, &end, 10);
	if (l > limit || end == NULL || *end != 0)
		return (false);
	if (opt == 'p')
		server->port = l;
	if (opt == 'x')
		server->map.width = l;
	if (opt == 'y')
		server->map.height = l;
	if (opt == 'c')
		server->max_clients = l;
	if (opt == 'f')
		server->freq = l;
	return (true);
}

static bool zpy_srv_args_parse_names(zpy_srv_t *server, int ac, char **av)
{
	int i = optind;
	int count;

	for (count = 0; i + count < ac && av[i + count][0] != '-'; count++);
	if (count == 0)
		return (false);
	for (i = 0 ; i < count; i++)
		list_push_back(server->teamnames, av[optind++]);
	return (true);
}

static bool zpy_srv_args_check_dup_name(zpy_srv_t *server, unsigned int i)
{
	list_node_t *cur;

	cur = list_get_node(server->teamnames, i);
	for (list_node_t *node = cur->next; node != NULL; node = node->next) {
		if (strcmp(cur->data, node->data) == 0)
			return (false);
	}
	return (true);
}

static bool zpy_srv_args_check(zpy_srv_t *server)
{
	if (server->port == 0)
		return (false);
	if (server->map.width == 0 || server->map.height == 0 ||
		server->max_clients == 0 || server->freq == 0)
		return (false);
	if (server->teamnames->len == 0)
		return (false);
	for (unsigned int i = 0; i < server->teamnames->len - 1; i++) {
		if (!zpy_srv_args_check_dup_name(server, i))
			return (false);
	}
	return (true);
}

bool zpy_srv_args_parse(zpy_srv_t *server, int ac, char **av)
{
	int opt;

	while (true) {
		opt = getopt(ac, av, "p:x:y:c:f:n");
		if (opt == -1)
			break;
		if (opt == '?')
			return (false);
		if (opt == 'p' &&
			!zpy_srv_args_parse_nbr(server, opt, optarg, USHRT_MAX))
			return (false);
		if ((opt == 'x' || opt == 'y' || opt == 'c' || opt == 'f') &&
			!zpy_srv_args_parse_nbr(server, opt, optarg, UINT_MAX))
			return (false);
		if (opt == 'n' &&
			!zpy_srv_args_parse_names(server, ac, av))
			return (false);
	}
	return (zpy_srv_args_check(server));
}