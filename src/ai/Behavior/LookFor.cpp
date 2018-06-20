#include <string>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** LookFor.cpp
*/

#include "LookFor.hpp"

zappy::ai::LookFor::LookFor(const zappy::RequestConstructor &requestConstructor)
	: _reqConst(requestConstructor)
{
}

std::string zappy::ai::LookFor::act()
{
	return _reqConst.look();
}

bool zappy::ai::LookFor::callback(const std::string &string)
{
	return false;
}
