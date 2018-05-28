/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy client main
*/

#include <stdio.h>
#include <string.h>

static int usage(char const *progname, int ret)
{
	printf("USAGE: %s -p port -n name -h machine\n", progname);
	puts("\tport\t\tis the port number");
	puts("\tname\t\tis the name of the team");
	puts("\tmachine\t\tis the name of the machine; localhost by default");
	return (ret);
}

int main(int argc, char const **argv)
{
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-help") == 0)
			return (usage(argv[0], 0));
	}
	return (0);
}
