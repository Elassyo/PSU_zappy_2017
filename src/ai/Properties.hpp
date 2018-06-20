/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Properties.hpp
*/

#ifndef PSU_ZAPPY_2017_PROPERTIES_HPP
	#define PSU_ZAPPY_2017_PROPERTIES_HPP

	#include <iostream>
	#include "Vertex.hpp"
	#include "Inventory.hpp"
	#include "Memory.hpp"

namespace zappy {
	namespace ai {
		enum Direction {
			NORTH = 0,
			EAST = 1,
			SOUTH = 2,
			WEST = 3,
			MAX = 4
		};
		class Properties {
		public:
			Properties();

			void moveForward();
			void turnRight();
			void turnLeft();
			void setTarget();
			void setNeed(Item);

			Vertex<size_t> getPos() const;
			Direction getDir() const;

		private:
			Vertex<size_t> _pos;
			Direction _dir;
			Vertex<size_t> _target;
			bool _alive;
			uint8_t _lvl;
			uint _food;
			uint _minFood;
			Inventory _inventory;
			Item _need;
			std::vector<Item> _lookingFor;
			const std::vector<Inventory> _lvlStuff;
			Memory _memory;
		};
	}
}

#endif /* PSU_ZAPPY_2017_PROPERTIES_HPP */