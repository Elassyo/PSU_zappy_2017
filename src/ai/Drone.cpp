//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.cpp
//

#include "Drone.hpp"

zappy::ai::Drone::Drone(const std::string &team,
			RequestHandler &requestHandler) :
	_team(team), _behave(LOOKFOR),
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
	std::string s;
	std::cout << "Begin to live" << std::endl;
	while (_properties.isAlive()) {
		_evaluatePriorities();
		s = _act.at(_behave)->act(_properties);
		std::cout << s << std::endl;
		_reqHandler.send(s);
		handleResponse();
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
		_properties.setLookingFor(_evaluateNeeds());
	}
}

bool zappy::ai::Drone::_canEvolve() const
{
	_reqHandler.send(_reqConstr.inventory());
	_reqHandler.fetch();
	std::cout << _reqHandler.recv() << std::endl;
	auto a = _properties.diff();
	return _properties.diff().empty();
}

std::vector<zappy::ai::Item> zappy::ai::Drone::_evaluateNeeds() const
{
	return _properties.diff();
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

bool zappy::ai::Drone::handleResponse()
{
	_reqHandler.fetch();
	std::string res = _reqHandler.recv();
	while (!_act.at(_behave)->callback(res, _properties)) {
		_reqHandler.fetch();
		res = _reqHandler.recv();
		std::cout << res << std::endl;
	}
	return true;
}
