/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Vision.hpp
*/

#ifndef PSU_ZAPPY_2017_VISION_HPP
	#define PSU_ZAPPY_2017_VISION_HPP

	#include <iostream>
	#include <vector>
	#include <sstream>
	#include "Tile.hpp"

namespace zappy {
	namespace ai {
		class Vision {
		public:
			explicit Vision(const std::string &);

			Tile getTile(uint8_t index) const;
			bool seeObject(Item) const;
			const zappy::VertexS getObject(zappy::ai::Item,
							const VertexS &pos,
		zappy::ai::Direction dir) const;
			Vision &operator=(const Vision &);
			~Vision() = default;
		private:
			std::vector<ai::Tile> _tiles;
		};
	}
}

#endif /* PSU_ZAPPY_2017_VISION_HPP */