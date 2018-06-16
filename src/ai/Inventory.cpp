//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Inventory.cpp
//

#include "Inventory.hpp"

zappy::ai::Inventory::Inventory()
{
	this->_items.insert(std::make_pair(zappy::ai::Item::NONE, 0));
	for (int i = zappy::ai::Item::FOOD; i <= THYSTAME; i++)
		this->_items.insert(std::make_pair((zappy::ai::Item)i, 0));
}

zappy::ai::Inventory::Inventory(const Inventory& ivent)
{
	for (auto it = this->_items.cbegin(); it != this->_items.cend(); ++it)
		this->_items.insert(std::make_pair(it->first, it->second));
}

zappy::ai::Inventory::Inventory(const std::string &itemStr)
{
	//itemStr from server, to parse
}

zappy::ai::Inventory::~Inventory() {}

size_t zappy::ai::Inventory::pick(const zappy::ai::Item item, const size_t nb)
{
	if (this->_items.at(item) >= nb)
		return this->_items.at(item) -= nb;
	return this->_items.at(item);
}

size_t zappy::ai::Inventory::add(const zappy::ai::Item item, const size_t nb)
{
	return this->_items.at(item) += nb;
}

size_t zappy::ai::Inventory::getNbr(const zappy::ai::Item item) const
{
	return this->_items.at(item);
}

bool zappy::ai::Inventory::operator==(const zappy::ai::Inventory &ivent) const
{
	auto ivent_it = ivent._items.cbegin();
	
	for (auto it = this->_items.cbegin(); it != this->_items.cend(); it++) {
		if (ivent_it->second != it->second)
			return false;
		ivent_it++;
	}
	return true;
}
