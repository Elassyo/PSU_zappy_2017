/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy ai main
*/

#include <cstring>
#include <iostream>

#include "CBuffer.hpp"

static int usage(char const *progname, int ret)
{
	std::cout << "USAGE: " << progname << " -p port -n name -h machine" <<
		std::endl;
	std::cout << "\tport\t\tis the port number" << std::endl;
	std::cout << "\tname\t\tis the name of the team" << std::endl;
	std::cout << "\tmachine\t\tis the name of the machine; " <<
		"localhost by default" << std::endl;
	return ret;
}

int main(int argc, char const **argv)
{
	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-help") == 0)
			return usage(argv[0], 0);
	}
	return 0;
}
