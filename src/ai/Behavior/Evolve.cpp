/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Evolve.cpp
*/

#include "Evolve.hpp"

zappy::ai::Evolve::Evolve(const zappy::RequestConstructor &rq) :
	_reqConst(rq), _evlState(CALL)
{
}

std::string zappy::ai::Evolve::act(zappy::ai::Properties &properties)
{
	switch (_evlState) {
	case CALL:
		return _call();
	case DROP:
		return _drop();
	case INCANTE:
		return _incante();
	}
	for (auto needed : properties.getLvlInventory
		(properties.getLvl() + 1).getItems()) {
		for (size_t i = 0; i < needed.second; i++)
			_reqConst.setObject(needed.first);
	}
	return _reqConst.incantation();
}

bool zappy::ai::Evolve::callback(const std::string &string,
				Properties &properties)
{
	return false;
}

void zappy::ai::Evolve::reset()
{
}

std::string zappy::ai::Evolve::_call()
{
	return _reqConst.broadcast("KREOOOOOOOOG !!!");
}

std::string zappy::ai::Evolve::_drop()
{
	return std::__cxx11::string();
}

std::string zappy::ai::Evolve::_incante()
{
	return std::__cxx11::string();
}
