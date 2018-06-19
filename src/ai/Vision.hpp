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
	#include "Exception/Exception.hpp"

namespace zappy {
	namespace ai {
		class Vision {
		public:
			Vision(const std::string &);
			~Vision() = default;

		private:
			std::vector<ai::Tile> _tiles;
		};
	}
}

#endif /* PSU_ZAPPY_2017_VISION_HPP */