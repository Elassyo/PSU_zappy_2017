//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// ParseArgs.hpp
//

#ifndef PARSEARGS_HPP_
# define PARSEARGS_HPP_

#include <iostream>
#include <cstring>

namespace zappy
{
	class ParseArgs
	{
	public:
		static bool isNumber(std::string str);
		static bool getPort(int argc, char const **argv, uint16_t &p);
		static bool getName(int argc, char const **argv, std::string &n);
		static bool getHostname(int argc, char const **argv,
			std::string &h);
		static bool printUsage(int argc, char const **argv);
	};
}

#endif /* !PARSEARGS_HPP_ */
