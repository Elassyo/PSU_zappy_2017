//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.hpp
//

#ifndef PSU_ZAPPY_2017_DRONE_HPP
	#define PSU_ZAPPY_2017_DRONE_HPP

	#include <vector>
	#include "Inventory.hpp"
	#include "Vertex.hpp"


namespace zappy {
	namespace ai {
		class Drone {
		public:
			explicit Drone(Vertex<size_t> pos);
			~Drone() = default;

		private:
			Vertex<size_t> _pos;
			Vertex<size_t> _target;
			uint8_t _lvl;
			Inventory _inventory;
			Item _need;
			std::vector<Item> _lookingFor;

		};
	}
}

#endif /* PSU_ZAPPY_2017_DRONE_HPP */