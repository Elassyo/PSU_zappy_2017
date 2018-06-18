/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Memory.hpp
*/

#ifndef PSU_ZAPPY_2017_MEMORY_HPP
	#define PSU_ZAPPY_2017_MEMORY_HPP

	#include <unordered_map>
	#include "Vertex.hpp"
	#include "Inventory.hpp"

namespace zappy {
	namespace ai {
		class Memory {
		public:
			Memory();
			~Memory() = default;

		private:
			std::unordered_map<Item, VertexS> _remembered;
		};
	}
}

#endif /* PSU_ZAPPY_2017_MEMORY_HPP */