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

			bool seeObject(Item) const;
			const zappy::VertexS getObject(zappy::ai::Item,
							const VertexS &pos,
							Direction dir) const;

			~Vision() = default;
		private:
			std::vector<ai::Tile> _tiles;
		};
	}
}

#endif /* PSU_ZAPPY_2017_VISION_HPP */