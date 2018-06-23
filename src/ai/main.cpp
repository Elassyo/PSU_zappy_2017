/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy AI main
*/

#include <cstring>
#include <iostream>

#include "Drone.hpp"
#include "ParseArgs.hpp"

int main(int argc, char const **argv)
{
	uint16_t port = 0;
	std::string name;
	std::string hostname;

	if (zappy::ParseArgs::printUsage(argc, argv))
		return (0);
	if (!zappy::ParseArgs::getPort(argc, argv, port) ||
		!zappy::ParseArgs::getName(argc, argv, name) ||
		!zappy::ParseArgs::getHostname(argc, argv, hostname))
		return (84);
	try {
		zappy::RequestHandler requestHandler(hostname, port);
		zappy::ai::Drone drone(name, requestHandler);
		drone.live();
	} catch (const zappy::Exception &e) {
		std::cerr << e.where() << ": "<<  e.what() << std::endl;
	}
	return 0;
}