#include <string>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Help.cpp
*/

#include "Help.hpp"

zappy::ai::Help::Help(const zappy::RequestConstructor &req) :
	_reqConst(req)
{
}

std::string zappy::ai::Help::act(Properties &properties)
{
	return _reqConst.broadcast("GOOOOERK !!!");
}

bool zappy::ai::Help::callback(const std::string &string, Properties &properties)
{
	return false;
}

void zappy::ai::Help::reset()
{

}
