/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Hunt.cpp
*/

#include "Hunt.hpp"

zappy::ai::Hunt::Hunt(const zappy::RequestConstructor &rstConst)
	: _rstConst(rstConst), _movement(_rstConst), _initTarget(false),
	  _moved(false)
{}

std::string zappy::ai::Hunt::act(zappy::ai::Properties &prop)
{
	if (!_initTarget) {
		prop.setTarget(prop.getPos() +
				VertexS(random() % 4 - 2, random() % 4 - 2));
		_initTarget = true;
	}
	if (prop.getPos() == prop.getTarget()) {
		_initTarget = false;
		_moved = false;
		return _rstConst.takeObject(FOOD);
	}
	auto a =_movement.move(prop);
	_moved = true;
	std::cerr << std::endl << a << std::endl;
	return a;
}

bool zappy::ai::Hunt::callback(const std::string &res,
			       zappy::ai::Properties &properties)
{
	return _moved ? _movement.moveBack(res, properties) :
		res == "ko" || res == "ok";
}

void zappy::ai::Hunt::reset()
{
	_initTarget = false;
}

bool zappy::ai::Hunt::handleMessage(zappy::ai::Properties &properties)
{
	return false;
}
