/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Memory.cpp
*/

#include "Memory.hpp"

zappy::ai::Memory::Memory()
{
}

bool zappy::ai::Memory::alreadySeen(zappy::ai::Item item) const
{
	return _remembered.find(item) != _remembered.end();
}

const zappy::VertexS zappy::ai::Memory::closestItem
	(Item item, const VertexS &pos) const
{
	auto range = _remembered.equal_range(item);
	VertexS vertex(range.first->second);
	VertexS closest(range.first->second);
	size_t dist = pow(pos.x() - vertex.x(), 2) +
		pow(pos.y() - vertex.y(), 2);
	size_t tmp;
	for (auto i = range.first; i != range.second; i++) {
		tmp = pow(pos.x() - vertex.x(), 2) +
			pow(pos.y() - vertex.y(), 2);
		vertex = i->second;
		if (tmp <= dist) {
			dist = tmp;
			closest = vertex;
		}
	}
	return closest;
}

void zappy::ai::Memory::remember(const zappy::VertexS &pos, zappy::ai::Item it)
{
	for (auto i = _remembered.begin(); i != _remembered.end(); i++) {
		if (i->second == pos) {
			_remembered.erase(i);
		}
	}
	_remembered.insert({it, pos});
}