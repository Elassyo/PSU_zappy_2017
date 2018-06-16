//
// EPITECH PROJECT, 2018
// Inventory.cpp
// File description:
//
//

#include "Inventory.hpp"


zappy::ai::Inventory::Inventory(const Inventory &other)
{
	_items = other._items;
}

zappy::ai::Inventory::Inventory(const std::string &string)
{

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

bool zappy::ai::Inventory::operator==(const zappy::ai::Inventory &other) const
{
	return _items == other._items;
}
