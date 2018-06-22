/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy AI main
*/

#include <cstring>
#include <iostream>

#include "Drone.hpp"

static int zpy_ai_usage(char const *progname, int ret)
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
	uint16_t port = 0;
	std::string name;
	std::string hostname;
	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-help") == 0)
			return zpy_ai_usage(argv[0], 0);
		if (argc > i + 1 && std::strcmp(argv[i], "-p") == 0)
			port = (uint16_t) atoi(argv[i + 1]);
		if (argc > i + 1 && std::strcmp(argv[i], "-n") == 0)
			name = argv[i + 1];
		if (argc > i + 1 && std::strcmp(argv[i], "-h") == 0)
			hostname = argv[i + 1];
	}
	try {
		zappy::RequestHandler requestHandler(hostname, port);
		zappy::ai::Drone drone(name, requestHandler);
		drone.live();
	} catch (const zappy::Exception &e) {
		std::cerr << e.where() << ": "<<  e.what() << std::endl;
	}

	return 0;
}
