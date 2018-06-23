/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Mean.cpp
*/

#include "Mean.hpp"

zappy::ai::Mean::Mean(const zappy::RequestConstructor &requestConstructor)
	: _lookState(LOOK), _rqsConst(requestConstructor)
{}

std::string zappy::ai::Mean::act(Properties &properties)
{
	(void)properties;
	switch (_lookState) {
	case LOOK:
		return "";
	case GO:
		return "";
	case TAKE:
		return "";
	}
	return "";
}

bool
zappy::ai::Mean::callback(const std::string &string, Properties &properties)
{
	(void)properties;
	(void)string;

	//use properties
	return false;
}

void zappy::ai::Mean::reset()
{
}
