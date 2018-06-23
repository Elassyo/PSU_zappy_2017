/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Helper.cpp
*/

#include "Helper.hpp"

bool zappy::Helper::isNumber(const std::string &str)
{
	for (char c : str) {
		if (!isdigit(c))
			return false;
	}
	return true;
}
