/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Tile.hpp
*/

#ifndef PSU_ZAPPY_2017_TILE_HPP
	#define PSU_ZAPPY_2017_TILE_HPP

	#include <sstream>
	#include <iostream>
	#include "Inventory.hpp"
	#include "Vertex.hpp"
	#include "Drone.hpp"

namespace zappy {
	namespace ai {
		class Tile {
		public:
			Tile(const std::string &itTiles);
			~Tile() = default;

			bool containsItem(Item) const;
			VertexS computePosition
				(const VertexS &playerPos,
				 ai::Direction, size_t) const;

		private:
			const static std::map<std::string, zappy::ai::Item>
			        _strItem;
			std::vector<zappy::ai::Item> _tileItems;
		};
	}
}

#endif /* PSU_ZAPPY_2017_TILE_HPP */