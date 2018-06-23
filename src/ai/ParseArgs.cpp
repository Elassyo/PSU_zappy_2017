//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// ParseArgs.cpp
//

#include "ParseArgs.hpp"

bool zappy::ParseArgs::isNumber(std::string str)
{
	int len = str.length();

	for (int i = 0; i < len; i++)
		if (str[i] < '0' || '9' < str[i])
			return false;
	return true;
}


bool zappy::ParseArgs::getPort(int argc, char const **argv, uint16_t &p)
{
	p = 0;
	for (int i = 1; i < argc; i++)
		if (argc > i + 1 && std::strcmp(argv[i], "-p") == 0) {
			if (zappy::ParseArgs::isNumber(argv[i + 1]) == false)
				return false;
			std::cout << argv[i + 1] << std::endl;
			p = (uint16_t) atoi(argv[i + 1]);
			return true;
		}
	return true;
}

bool zappy::ParseArgs::getName(int argc, char const **argv,
	std::string &n)
{
	n = "defaultTeamName";
	for (int i = 1; i < argc; i++) {
		if (argc > i + 1 && std::strcmp(argv[i], "-n") == 0) {
			n = argv[i + 1];
			return true;
		}
	}
	return true;
}

bool zappy::ParseArgs::getHostname(int argc, char const **argv,
	std::string &h)
{
	h = "0.0.0.0";
	for (int i = 1; i < argc; i++) {
		if (argc > i + 1 && std::strcmp(argv[i], "-h") == 0) {
			h = argv[i + 1];
			return true;
		}
	}
	return true;
}

bool zappy::ParseArgs::printUsage(int argc, char const **argv)
{
	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-help") == 0) {
			std::cout << "USAGE: " << argv[0]
				<< " -p port -n name -h machine"
				<< std::endl;
			std::cout << "\tport\t\tis the port number"
				<< std::endl;
			std::cout << "\tname\t\tis the name of the team"
				<< std::endl;
			std::cout << "\tmachine\t\tis the name of the machine;"
				<< " localhost by default" << std::endl;
			return true;
		}
	}
	return false;
}
