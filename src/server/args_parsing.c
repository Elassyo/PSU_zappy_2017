/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** testing.c
*/

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "args.h"

const char arg_str[] = "p:x:y:n:c:f:";

static void init_args(args_t *args)
{
	args->names = NULL;
	args->freq = 0;
	args->clients = 0;
	args->height = 0;
	args->width = 0;
	args->port = 0;
}

static int count_names(int ac, char const **av, int i)
{
	int res = 0;

	for (; i < ac && strncmp(av[i], "-", 1) != 0; i++)
		res++;
	return (res);
}

static void get_names(args_t *args, int ac, char const **av, int i)
{
	int names_count = count_names(ac, av, i);

	args->names = malloc(sizeof(char *) * (names_count + 1));
	if (args->names == NULL)
		return;
	args->names[names_count] = NULL;
	for (int j = 0; j < names_count; j++)
		args->names[j] = strdup(av[i + j]);
}


static int get_args(args_t *args, int ac, char const **av)
{
	int opt = 0;

	while ((opt = getopt(ac, (char *const *) av, arg_str)) != -1) {
		if (opt == 'p')
			args->port = atoi(optarg);
		else if (opt == 'x')
			args->width = atoi(optarg);
		else if (opt == 'y')
			args->height = atoi(optarg);
		else if (opt == 'n')
			get_names(args, ac, av, optind - 1);
		else if (opt == 'c')
			args->clients = atoi(optarg);
		else if (opt == 'f')
			args->freq = atoi(optarg);
	}
	return (0);
}

int parse_args(args_t *args, int ac, char const **av)
{
	init_args(args);
	get_args(args, ac, av);
	if (args->port < 0 ||
		args->height <= 0 ||
		args->width <= 0 ||
		args->clients <= 0 ||
		args->freq <= 0 ||
		args->names == NULL)
		return (-1);
	return (0);
}
