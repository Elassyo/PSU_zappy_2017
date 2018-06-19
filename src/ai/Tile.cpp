/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

zappy::ai::Tile::Tile(const std::string &itTile) :
	_strItem({
			 {"player", ai::Item::DRONE},
			 {"food", ai::Item::FOOD},
			 {"linemate", ai::Item::LINEMATE},
			 {"deraumere", ai::Item::DERAUMERE},
			 {"sibur", ai::Item::SIBUR},
			 {"mendiane", ai::Item::MENDIANE},
			 {"phiras", ai::Item::PHIRAS},
			 {"thystame", ai::Item::THYSTAME}})
{
	std::stringstream ss(itTile);
	std::string token;

	while (ss >> token)
		_tileItems.emplace_back(_strItem[token]);
}

zappy::VertexS zappy::ai::Tile::computePosition(const zappy::VertexS &playerPos,
						const zappy::VertexS &mapSize,
						zappy::ai::Direction) const
{

	return VertexS(0, 0);
}
