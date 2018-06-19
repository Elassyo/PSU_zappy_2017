/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Vision.cpp
*/

#include "Vision.hpp"

zappy::ai::Vision::Vision(const std::string &rsp)
{
	size_t len = rsp.length();

	if (rsp[0] != '[' && rsp[len - 1] != ']')
		throw Exception("Vision", "Vision string malformed");

	std::stringstream ss(rsp.substr(1, len - 2));
	std::string token;

	for (size_t i = 0; std::getline(ss, token, ','); i++)
		this->_tiles.emplace_back(Tile(token));
}