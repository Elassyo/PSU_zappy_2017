/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Movement.cpp
*/

#include "Movement.hpp"

zappy::ai::Movement::Movement(const RequestConstructor &requestConstructor) :
	_reqConst(requestConstructor),
	_cor({{NORTH, std::bind(&Movement::_fromNorth, this, std::placeholders::_1)},
	      {SOUTH, std::bind(&Movement::_fromSouth, this, std::placeholders::_1)},
	      {EAST, std::bind(&Movement::_fromEast, this, std::placeholders::_1)},
	      {WEST, std::bind(&Movement::_fromWest, this, std::placeholders::_1)}})
{

}

std::string zappy::ai::Movement::move(zappy::ai::Properties &properties)
{
	std::string s = _cor[properties.getDir()](properties);
	if (s.empty()) {
		_lastAction = "move";
		return _reqConst.moveForward();
	}
	_lastAction = s;
	return s;
}

bool
zappy::ai::Movement::moveBack(const std::string &res, zappy::ai::Properties &prop)
{
	if (res != "ok")
		return false;
	std::cerr << res << std::endl;
	if (_lastAction == "move")
		prop.moveForward();
	else if (_lastAction == _reqConst.turnLeft())
		prop.turnLeft();
	else
		prop.turnRight();
	return true;
}

std::string zappy::ai::Movement::_fromNorth(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
		       _reqConst.turnRight() : _reqConst.turnLeft();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       "" : _reqConst.turnRight();
	}
}

std::string zappy::ai::Movement::_fromSouth(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
		       _reqConst.turnLeft() : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() < prp.getPos().y() ?
		       "" : _reqConst.turnRight();
	}
}

std::string zappy::ai::Movement::_fromEast(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
		       "" : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       _reqConst.turnLeft() : _reqConst.turnRight();
	}

}

std::string zappy::ai::Movement::_fromWest(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() < prp.getPos().x() ?
		       "" : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       _reqConst.turnRight() : _reqConst.turnLeft();
	}

}