#include <string>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Help.cpp
*/

#include "Help.hpp"
#include "../Exception/Exception.hpp"

zappy::ai::Help::Help(const zappy::RequestConstructor &req) :
	_reqConst(req), _vec({VertexS(0, 1), VertexS(-1, -1), VertexS(-1, 0),
			      VertexS(-1, -1), VertexS(0, -1), VertexS(1, -1),
			      VertexS(1, 0), VertexS(1, 1)}), _mov(req),
	_toAdd(1, 0), _answered(false), _xDone(false)
{
}

std::string zappy::ai::Help::act(Properties &properties)
{
	switch (_helpState) {
	case HEAR:
		return _hear(properties);
	case WALK:
		return _walk(properties);
	case ARRIVED:
		return _arrived(properties);
	}
	return _mov.move(properties);
}

std::string zappy::ai::Help::_walk(zappy::ai::Properties &prp)
{
	if (prp.getPos() == prp.getTarget()) {
		_answered = false;
		_helpState = HEAR;
		return "";
	}
	return _mov.move(prp);
}

std::string zappy::ai::Help::_hear(zappy::ai::Properties &prp)
{
	static size_t loop = 0;
	if (!_answered)
		return _reqConst.broadcast("GOERK" + std::to_string(loop++));
	_helpState = WALK;
	_lastCallPos = _calcPos(prp, _lastHeared);
	if (_lastCallPos.x() == prp.getPos().x()) {
		_toAdd = {0, 1};
	}
	prp.setTarget(prp.getPos() + _toAdd);
	return "";
}

std::string zappy::ai::Help::_arrived(zappy::ai::Properties &prp)
{
	if (!_evlLaunched) {
		prp.setEvolving(true);
		return _reqConst.broadcast("HERE");
	}
	return "wait";
}

zappy::VertexS
zappy::ai::Help::_calcPos(zappy::ai::Properties &prop, uint8_t dir)
{
	int index = (8 - 2 * (prop.getDir()) + dir) % 8;

	if (index == 0)
		index = 8;
	--index;
	std::cout << (_vec[index] + prop.getPos()).x() << "   " <<
		(_vec[index] + prop.getPos()).y() << std::endl;
	return _vec[index] + prop.getPos();
}

bool zappy::ai::Help::callback(const std::string &res, Properties &properties)
{
	switch (_helpState) {
	case HEAR:
		return _hearBack(res, properties);
	case WALK:
		return _walkBack(res, properties);
	case ARRIVED:
		return _arrivedBack(res, properties);
	}
	throw Exception("Help", "Help doesn't have any state");
}


bool zappy::ai::Help::_walkBack
	(const std::string &res, zappy::ai::Properties &prp)
{
	return _mov.moveBack(res, prp);
}

bool zappy::ai::Help::_hearBack
	(const std::string &res, zappy::ai::Properties &prp)
{
	return res == "ok";
}

bool zappy::ai::Help::_arrivedBack
	(const std::string &res, zappy::ai::Properties &prp)
{
	if (res == "Elevation underway") {
		return true;
	} else if (res.find("Current level:") != std::string::npos) {
		prp.addLvl();
		prp.setEvolving(false);
		return true;
	}
	return false;
}

void zappy::ai::Help::reset()
{
	_answered = false;
}

bool zappy::ai::Help::handleMessage(zappy::ai::Properties &prp)
{
	auto pair = prp.getMsg();

	if (pair.second.find("KREOG") != std::string::npos) {
		_answered = true;
		if (pair.first == 0) {
			_helpState = ARRIVED;
			return true;
		}
		_lastHeared = pair.first;
		prp.setMsg("", 0);
	}
	return false;
}
