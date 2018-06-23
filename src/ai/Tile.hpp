/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Tile.hpp
*/

#ifndef PSU_ZAPPY_2017_TILE_HPP
	#define PSU_ZAPPY_2017_TILE_HPP

	#include <sstream>
	#include <map>
	#include <vector>
	#include "Vertex.hpp"
	#include "Inventory.hpp"

namespace zappy {
	namespace ai {
		enum Direction {
			NORTH = 0,
			EAST = 1,
			SOUTH = 2,
			WEST = 3,
			MAX = 4
		};
		class Tile {
		public:
			explicit Tile(const std::string &itTiles);
			~Tile() = default;

			bool containsItem(Item) const;
			Item getItem() const;
			bool empty() const;
			ssize_t nbrItem(Item) const;
			VertexS computePosition
				(const VertexS &playerPos,
				Direction, size_t) const;

		private:
			const static std::map<std::string, zappy::ai::Item>
			        _strItem;
			std::vector<zappy::ai::Item> _tileItems;
		};
	}
}

#endif /* PSU_ZAPPY_2017_TILE_HPP */