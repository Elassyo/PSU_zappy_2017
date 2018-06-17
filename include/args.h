/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** args.h
*/


#ifndef ARGS_H
#define ARGS_H

extern const char arg_str[];

typedef struct args_s {
	int port;
	int width;
	int height;
	int clients;
	int freq;
	char **names;
} args_t;

int parse_args(args_t *args, int ac, char const **av);

#endif //ARGS_H
