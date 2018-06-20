/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Vision.cpp
*/

#include "Vision.hpp"
#include "Exception/Exception.hpp"

zappy::ai::Vision::Vision(const std::string &rsp)
{
	if (rsp.empty())
		return;
	size_t len = rsp.length();

	if (rsp[0] != '[' && rsp[len - 1] != ']')
		throw Exception("Vision", "Vision string malformed");

	std::stringstream ss(rsp.substr(1, len - 2));
	std::string token;

	for (size_t i = 0; std::getline(ss, token, ','); i++)
		this->_tiles.emplace_back(Tile(token));
}

bool zappy::ai::Vision::seeObject(zappy::ai::Item item) const
{
	for (const Tile &tile : _tiles)
		if (tile.containsItem(item))
			return true;
	return false;
}

const zappy::VertexS zappy::ai::Vision::getObject(zappy::ai::Item item,
						const VertexS &pos,
						Direction dir) const
{
	for (size_t i = 0, len = _tiles.size(); i < len ;i++) {
		if (_tiles[i].containsItem(item))
			return _tiles[i].computePosition(pos, dir, i);
	}
	throw Exception("Vision", "Item doesn't exist");
}

zappy::ai::Vision &zappy::ai::Vision::operator=(const zappy::ai::Vision &vision)
{
	_tiles = vision._tiles;
	return *this;
}
