//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.cpp
//

#include "Drone.hpp"


const std::map<zappy::ai::Behavior, std::string> cor = {
	{zappy::ai::EVOLVE ,"evolve"},
	{zappy::ai::Behavior::LOOKFOR ,"lookfor"},
	{zappy::ai::Behavior::HUNT, "hunt"},
	{zappy::ai::Behavior::HELP,"help"}};

zappy::ai::Drone::Drone(const std::string &team,
			RequestHandler &requestHandler) :
	_team(team), _behave(LOOKFOR),
	_act({make_pair(EVOLVE, std::make_shared<Evolve>(_reqConstr)),
	      make_pair(LOOKFOR, std::make_shared<LookFor>(_reqConstr)),
	      make_pair(HUNT, std::make_shared<Hunt>(_reqConstr)),
	      make_pair(HELP, std::make_shared<Help>(_reqConstr))}),
	_reqHandler(requestHandler),
	_maxFood(8)
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
		if (!_properties.isEvolving())
			_updateInventory();
		std::cout << "Evaluate priorities" << std::endl;
		_evaluatePriorities();
		std::cout << "Evaluate priorities done" << std::endl;
		s = _act.at(_behave)->act(_properties);
		std::cout << "POS : " << _properties.getPos().x() << " " << _properties.getPos().y() << std::endl;
		std::cout << "TARGET : " << _properties.getTarget().x() << " " << _properties.getTarget().y() << std::endl;
		std::cout << "FOOD : " << _properties.getFood() << std::endl;
		std::cout << "LVL : " << _properties.getLvl() << std::endl;
		std::cout << "\n\n\n" << cor.at(_behave) << "\n\n\n";
		std::cout << "COMMAND : " << s << std::endl;
		if (s == "wait") {
			handleResponse();
		} else if (!s.empty()) {
			_reqHandler.send(s);
			std::cout << "Message " << s;
			handleResponse();
			std::cout << "Response handled" << std::endl;
		}
	}
	return false;
}

void zappy::ai::Drone::_evaluatePriorities()
{
	if (_properties.getFood() <= _properties.getMinFood() ||
		(_behave == HUNT && _properties.getFood() < _maxFood)) {
		_behave = HUNT;
	} else if (_properties.isEvolving() || _canEvolve()) {
		_behave = EVOLVE;
		_properties.setNeed(NONE);
	} else if (_behave != HELP) {
		_behave = LOOKFOR;
		_properties.setLookingFor(_evaluateNeeds());
	}
	_handleMessage();
}

bool zappy::ai::Drone::_handleMessage()
{
	auto pair = _properties.getMsg();
	if (_properties.getMsg().second.empty())
		return false;
	if (pair.second.find("KREOG") != std::string::npos) {
		_behave = HELP;
	}
	return true;
}

void zappy::ai::Drone::_updateInventory()
{
	_reqHandler.send(_reqConstr.inventory());
	_reqHandler.fetch();
	std::string res = _reqHandler.recv();
	bool con = true;
	while (con) {
		try {
			Inventory inv = _reqParser.parseInventory(res);
			_properties.setFood(inv.getNbr(FOOD));
			con = false;
		} catch (const Exception &) {
			res = _reqHandler.recv();
			con = true;
		}
	}
}

bool zappy::ai::Drone::_canEvolve() const
{
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
	std::string res = _reqHandler.recv();
	std::cout << "RESPONSE = " << res << std::endl;
	while (!_reqParser.isEvent(res, _properties) &&
		!_act.at(_behave)->callback(res, _properties)) {
		std::cout << "Message not parsed fetch again" << std::endl;
		res = _reqHandler.recv();
		std::cout << res << std::endl;
	}
	return true;
}
