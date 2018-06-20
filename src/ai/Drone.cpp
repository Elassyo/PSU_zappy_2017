//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.cpp
//

#include "Drone.hpp"

zappy::ai::Drone::Drone(const std::string &team, const VertexS &mapSize,
			RequestHandler &requestHandler) :
	_team(team),
	_act({make_pair(EVOLVE, std::make_shared<Evolve>(_reqConstr)),
	      make_pair(LOOKFOR, std::make_shared<LookFor>(_reqConstr)),
	      make_pair(HELP, std::make_shared<Help>(_reqConstr))}),
	_reqHandler(requestHandler)
{
	_reqHandler.fetch();
	std::string welcome = _reqHandler.recv();
	std::cout << welcome << std::endl;
	if (welcome != "WELCOME")
		throw Exception("Drone", "Welcome msg expected");
	_reqHandler.send(_team + "\n");
	_reqHandler.fetch();
	welcome = _reqHandler.recv();
	welcome = _reqHandler.recv();
}

bool zappy::ai::Drone::live()
{
	std::cout << "Begin to live" << std::endl;
	while (_properties.isAlive()) {
		_evaluatePriorities();
		_act.at(_behave)->act(_properties);
	}
	return false;
}

void zappy::ai::Drone::_evaluatePriorities()
{
	if (_properties.getFood() <= _properties.getMinFood()) {
		_properties.setNeed(FOOD);
		_behave = LOOKFOR;
	} else if (_canEvolve()) {
		_behave = EVOLVE;
		_properties.setNeed(NONE);
	} else {
		_behave = LOOKFOR;
		_evaluateNeeds();
	}
}

bool zappy::ai::Drone::_canEvolve() const
{
	return false;
}

std::vector<zappy::ai::Item> zappy::ai::Drone::_evaluateNeeds() const
{
	return _properties.diff();
}

void zappy::ai::Drone::_move(const zappy::VertexS &dir)
{
}

void zappy::ai::Drone::_look()
{
	_reqHandler.send(_reqConstr.look());
}

bool zappy::ai::Drone::_take(zappy::ai::Item)
{
	_reqConstr.takeObject(Item::FOOD);
	return false;
}

void zappy::ai::Drone::setTarget()
{
}

bool
zappy::ai::Drone::handleResponse(std::function<bool(const std::string &)> fun)
{
	_reqHandler.fetch();
	std::string res = _reqHandler.recv();
	while (!fun(res)) {
		_reqHandler.fetch();
		res = _reqHandler.recv();
	}
	return true;
}
