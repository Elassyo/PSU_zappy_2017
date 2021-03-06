/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Tile.cpp
*/

#include <cmath>
#include <algorithm>
#include "Tile.hpp"
#include "Exception/Exception.hpp"

const std::map<std::string, zappy::ai::Item> zappy::ai::Tile::_strItem = {
	{"player", ai::Item::DRONE},
	{"food", ai::Item::FOOD},
	{"linemate", ai::Item::LINEMATE},
	{"deraumere", ai::Item::DERAUMERE},
	{"sibur", ai::Item::SIBUR},
	{"mendiane", ai::Item::MENDIANE},
	{"phiras", ai::Item::PHIRAS},
	{"thystame", ai::Item::THYSTAME}
};


zappy::ai::Tile::Tile(const std::string &itTile)
{
	std::stringstream ss(itTile);
	std::string token;

	while (ss >> token) {
		if (_strItem.find(token) != _strItem.end())
			_tileItems.emplace_back(_strItem.at(token));
		else
			throw Exception("Tile", "token is not item");
	}
}

zappy::VertexS zappy::ai::Tile::computePosition(const zappy::VertexS &playerPos,
						zappy::ai::Direction dir,
						size_t index) const
{
	size_t y = (size_t) std::trunc(sqrt(index));
	switch (dir) {
	case NORTH:
		return playerPos + VertexS(index - y *(y + 1), y);
	case SOUTH:
		return playerPos + VertexS((index - y *(y + 1)) * (-1), y * (-1));
	case EAST:
		return playerPos + VertexS(y, (index - y *(y + 1)) * (-1));
	case WEST:
		return playerPos + VertexS(y * (-1), index - y *(y + 1));
	default:
		return playerPos;
	}

}

bool zappy::ai::Tile::empty() const
{
	size_t i = 0;
	for (i = 0; i < _tileItems.size() && _tileItems.at(i) == DRONE; i++);
	return i == _tileItems.size();
}

zappy::ai::Item zappy::ai::Tile::getItem() const
{
	size_t i = 0;
	for (i = 0; _tileItems.at(i) == DRONE && i < _tileItems.size(); i++);
	return i == _tileItems.size() ? DRONE : _tileItems.at(i);
}

ssize_t zappy::ai::Tile::nbrItem(zappy::ai::Item item) const
{
	int nbr = 0;
	for (Item tileItem : _tileItems)
		if (item == tileItem)
			++nbr;
	return nbr;
}

bool zappy::ai::Tile::containsItem(Item item) const
{
	return std::find(_tileItems.begin(), _tileItems.end(), item)
		!= _tileItems.end();
}
