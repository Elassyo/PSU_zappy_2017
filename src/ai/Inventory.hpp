//
// EPITECH PROJECT, 2018
// Inventory.hpp
// File description:
//
//

#ifndef INVENTORY_HPP_
# define INVENTORY_HPP_

#include <iostream>
#include <map>
#include <vector>

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
			  THYSTAME};
		class Inventory
		{
		public:
			explicit Inventory() = default;
			explicit Inventory(const Inventory &);
			explicit Inventory(const std::map<Item, size_t> &);
			explicit Inventory(size_t linemate, size_t deraumere,
					   size_t sibur, size_t mendiane,
					   size_t phiras, size_t thystame);
			~Inventory() = default;

			size_t pick(const Item, const size_t nb);
			size_t add(const Item, const size_t nb);
			size_t getNbr(const Item) const;

			std::vector<Item> diff(const Inventory &) const;

			bool operator==(const Inventory &) const;
			bool operator>=(const Inventory &) const;

		private:
			std::map<Item, size_t> _items;
		};
	}
}	

#endif /* !INVENTORY_HPP_ */
