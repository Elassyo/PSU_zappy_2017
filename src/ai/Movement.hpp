/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Movement.hpp
*/

#ifndef PSU_ZAPPY_2017_MOVEMENT_HPP
	#define PSU_ZAPPY_2017_MOVEMENT_HPP

	#include <functional>
	#include "Tile.hpp"
	#include "Properties.hpp"
	#include "RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		class Movement {
		public:
			Movement(const RequestConstructor &);
			std::string move(Properties &properties);
			bool moveBack(const std::string &, Properties &prp);

		private:
			std::string _fromNorth(Properties &prp);
			std::string _fromSouth(Properties &prp);
			std::string _fromEast(Properties &prp);
			std::string _fromWest(Properties &prp);
			const RequestConstructor &_reqConst;
			std::string _lastAction;
			std::map<Direction, std::function<std::string(Properties &)>> _cor;
		};
	}
}

#endif /* PSU_ZAPPY_2017_MOVEMENT_HPP */