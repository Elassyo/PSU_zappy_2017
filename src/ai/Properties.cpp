/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Properties.cpp
*/

#include "Properties.hpp"

zappy::ai::Properties::Properties()
{

}

void zappy::ai::Properties::moveForward()
{
	if (_dir % 2 == 0)
		_pos.ry() += _dir == NORTH ? 1 : -1;
	else
		_pos.rx() += _dir == EAST ? 1 : -1;
}

void zappy::ai::Properties::turnRight()
{
	_dir = (Direction) ((_dir + 1) % MAX);
}

void zappy::ai::Properties::turnLeft()
{
	_dir = (Direction) (_dir ? _dir - 1 : MAX - 1);
}

void zappy::ai::Properties::setNeed(zappy::ai::Item item)
{
	_need = item;
}

void zappy::ai::Properties::setTarget()
{
	if (_need != NONE) {
		if (_memory.alreadySeen(_need))
			_target = _memory.closestItem(_need, _pos);
	}
}

zappy::Vertex<size_t> zappy::ai::Properties::getPos() const
{
	return _pos;
}

zappy::ai::Direction zappy::ai::Properties::getDir() const
{
	return _dir;
}
