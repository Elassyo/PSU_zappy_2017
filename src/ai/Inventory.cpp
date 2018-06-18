//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Inventory.cpp
//

#include "Inventory.hpp"

zappy::ai::Inventory::Inventory(const Inventory &other)
{
	_items = other._items;
}

zappy::ai::Inventory::Inventory(size_t linemate, size_t deraumere,
				size_t sibur, size_t mendiane, size_t phiras,
				size_t thystame) :
	_items({{LINEMATE, linemate},
		{DERAUMERE, deraumere},
		{SIBUR, sibur},
		{MENDIANE, mendiane},
		{PHIRAS, phiras},
		{THYSTAME, thystame}})
{
}

zappy::ai::Inventory::Inventory(const std::map<zappy::ai::Item, size_t> &itemNbr)
{
	this->_items = itemNbr;
}

size_t zappy::ai::Inventory::pick(const zappy::ai::Item item, const size_t nb)
{
	if (_items.find(item) == _items.end())
		return 0;
	if (_items[item] <= nb) {
		size_t t = _items[item];
		_items[item] = 0;
		return t;
	}
	_items[item] -= nb;
	return nb;
}

size_t zappy::ai::Inventory::add(const zappy::ai::Item item, const size_t nb)
{
	if (_items.find(item) == _items.end()) {
		_items[item] = nb;
		return nb;
	}
	_items[item] += nb;
	return _items[item];

}

size_t zappy::ai::Inventory::getNbr(const zappy::ai::Item item) const
{
	return _items.at(item);
}

std::vector<zappy::ai::Item> zappy::ai::Inventory::diff
	(const zappy::ai::Inventory &other) const
{
	std::vector<Item> need;

	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (_items.find(i->first) != _items.end()) {
			for (int c =
				other._items.at(i->first) - _items.at(i->first);
			     c < 0; c--)
				need.push_back(i->first);
		}
	}
	return need;
}

bool zappy::ai::Inventory::operator==(const zappy::ai::Inventory &other) const
{
	return _items == other._items;
}

bool zappy::ai::Inventory::operator>=(const zappy::ai::Inventory &other) const
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (this->_items.find(i->first) != this->_items.end() ||
		    this->_items.at(i->first) < other._items.at(i->first))
			return false;
	}
	return true;
}
