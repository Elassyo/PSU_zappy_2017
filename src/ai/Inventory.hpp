//
// EPITECH PROJECT, 2018
// Inventory.hpp
// File description:
//
//

#ifndef INVENTORY_HPP_
# define INVENTORY_HPP_

#include <iostream>
#include <unordered_map>

namespace zappy
{
	namespace ai
	{
		enum Item{NONE = 0,
			  FOOD,
			  LINEMATE,
			  DERAUMERE,
			  SIBUR,
			  MENDIANE,
			  PHIRAS,
			  THYSTAME}
		class Inventory
		{
		public:
			explicit Inventory();
			explicit Inventory(const Inventory &);
			explicit Inventory(const std::string &);
			~Inventory();

			size_t pick(const Item, const size_t nb);
			size_t add(const Item, const size_t nb);
			size_t getNbr(const Item) const;

			bool operator==(const Inventory &) const;

		private:
			std::unordered_map<Item, size_t> _items;
		};
	}
}	

#endif /* !INVENTORY_HPP_ */
