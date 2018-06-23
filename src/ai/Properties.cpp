/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Properties.cpp
*/

#include <algorithm>
#include "Properties.hpp"
#include "Exception/Exception.hpp"

zappy::ai::Properties::Properties() :
	_pos(0, 0), _dir(NORTH), _target(0, 0), _alive(true),
	_lvl(1), _food(10), _minFood(3),
	_inventory(0, 0, 0, 0, 0, 0), _need(NONE),
	_lvlStuff({Inventory(1, 0, 0, 0, 0, 0), Inventory(1, 1, 1, 0, 0, 0),
		   Inventory(2, 0, 1, 0, 2, 0), Inventory(1, 1, 2, 0, 1, 0),
		   Inventory(1, 2, 1, 3, 0, 0), Inventory(1, 2, 3, 0, 1, 0),
		   Inventory(2, 2, 2, 2, 2, 1)}),
	_lvlplayers({1, 2, 2, 4, 4, 6, 6}),
	_vision(""), _isEvolving(false)
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

void zappy::ai::Properties::setTarget(const VertexS &pos)
{
	_target = pos;
}

void zappy::ai::Properties::addLookingFor(zappy::ai::Item item)
{
	_lookingFor.emplace_back(item);
}

void zappy::ai::Properties::pickLookingFor(zappy::ai::Item item)
{
	auto it = std::find(_lookingFor.begin(), _lookingFor.end(), item);
	if (it == _lookingFor.end())
		throw Exception("Properties", "can't pick lookingFor item");
	_lookingFor.erase(it);
}

void zappy::ai::Properties::setLookingFor(const std::vector<zappy::ai::Item> &l)
{
	_lookingFor = l;
}

void zappy::ai::Properties::addLvl()
{
	_lvl++;
}

void zappy::ai::Properties::setFood(uint amount)
{
	_food = amount;
}

void zappy::ai::Properties::addItem(zappy::ai::Item item)
{
	_inventory.add(item, 1);
}

void zappy::ai::Properties::dropItem(zappy::ai::Item item)
{
	_inventory.pick(item, 1);
}

std::vector<zappy::ai::Item> zappy::ai::Properties::diff() const
{
	return _inventory.diff(_lvlStuff.at(_lvl - 1));
}

void zappy::ai::Properties::setVision(const zappy::ai::Vision &vision)
{
	_vision = vision;
}

void zappy::ai::Properties::setEvolving(bool b)
{
	_isEvolving = b;
}

void zappy::ai::Properties::kill()
{
	_alive = false;
}

void zappy::ai::Properties::setMsg(const std::string &msg, uint8_t from)
{
	_msg = msg;
	_fromMsg = from;
}

void zappy::ai::Properties::setMsg(std::pair<const std::string &, uint8_t> pair)
{
	_msg = pair.first;
	_fromMsg = pair.second;
}

zappy::VertexS zappy::ai::Properties::getPos() const
{
	return _pos;
}

zappy::ai::Direction zappy::ai::Properties::getDir() const
{
	return _dir;
}

bool zappy::ai::Properties::isAlive() const
{
	return _alive;
}

uint8_t zappy::ai::Properties::getLvl() const
{
	return _lvl;
}

uint zappy::ai::Properties::getFood() const
{
	return _food;
}

const zappy::VertexS &zappy::ai::Properties::getTarget() const
{
	return _target;
}

uint zappy::ai::Properties::getMinFood() const
{
	return _minFood;
}

size_t zappy::ai::Properties::nbrItem(zappy::ai::Item item) const
{
	return _inventory.getNbr(item);
}

zappy::ai::Item zappy::ai::Properties::getNeed() const
{
	return _need;
}

const std::vector<zappy::ai::Item> &zappy::ai::Properties::getLookingFor() const
{
	return _lookingFor;
}

const zappy::ai::Inventory &zappy::ai::Properties::getLvlInventory
	(uint8_t lvl) const
{
	return _lvlStuff.at((uint) lvl - 1);
}

uint8_t zappy::ai::Properties::getLvlPlayers(uint8_t lvl) const
{
	return _lvlplayers.at(lvl - 1);
}

const zappy::ai::Vision &zappy::ai::Properties::getVision() const
{
	return _vision;
}

bool zappy::ai::Properties::isEvolving() const
{
	return _isEvolving;
}

std::pair<uint8_t, const std::string &>zappy::ai::Properties::getMsg() const
{
	return std::make_pair(_fromMsg, _msg);
}
