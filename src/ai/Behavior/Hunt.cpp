/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Hunt.cpp
*/

#include "Hunt.hpp"

zappy::ai::Hunt::Hunt(const zappy::RequestConstructor &rstConst)
	: _rstConst(rstConst), _movement(_rstConst), _initTarget(false)
{}

std::string zappy::ai::Hunt::act(zappy::ai::Properties &prop)
{
	if (!_initTarget) {
		prop.setTarget(prop.getPos() +
				VertexS(random() % 2, random() % 2));
		_initTarget = true;
	}
	if (prop.getPos() == prop.getTarget()) {
		_initTarget = false;
		return _rstConst.takeObject(FOOD);
	}
	return _movement.move(prop);
}

bool zappy::ai::Hunt::callback(const std::string &res,
			       zappy::ai::Properties &properties)
{
	return res == "ok" || res == "ko";
}

void zappy::ai::Hunt::reset()
{
	_initTarget = false;
}