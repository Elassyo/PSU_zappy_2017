#include <string>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Help.cpp
*/

#include "Help.hpp"

zappy::ai::Help::Help(const zappy::RequestConstructor &req) :
	_reqConst(req), _vec({VertexS(0, 1), VertexS(-1, -1), VertexS(-1, 0),
			      VertexS(-1, -1), VertexS(0, -1), VertexS(1, -1),
			      VertexS(1, 0), VertexS(1, 1)}), _mov(req),
	_answered(false), _arrived(false), _moving(false), _toAdd(1, 0),
	_ret(false)
{
}

std::string zappy::ai::Help::act(Properties &properties)
{
	if (_arrived)
		return "wait";
	auto pair = properties.getMsg();
	if (!_answered) {
		_moving = false;
		return _reqConst.broadcast("GOERK");
	}
	properties.setMsg("", 0);
	if (properties.getPos() == properties.getTarget() && _moving) {
		_moving = false;
		return _reqConst.broadcast("GOERK");
	} else if (properties.getPos() == properties.getTarget())
		return "recMsg";
	if (!pair.second.empty() && !_moving) {
		_lastCallPos = _calcPos(properties, pair.first);
		_moving = true;
		properties.setMsg(std::make_pair("", 0));
	}
	if (pair.first == 0 && !pair.second.empty()) {
		_arrived = true;
		properties.setEvolving(true);
		_moving = false;
		return _reqConst.broadcast("HERE");
	}
	if (_lastCallPos.x() == 0)
		_toAdd = {0, 1};
	if (_moving)
		properties.setTarget(properties.getPos() + _toAdd);
	return _mov.move(properties);
}

zappy::VertexS
zappy::ai::Help::_calcPos(zappy::ai::Properties &prop, uint8_t dir)
{
	int index = (8 - 2 * (prop.getDir()) + dir) % 8;

	if (index == 0)
		index = 8;
	--index;
	std::cout << (_vec[index] + prop.getPos()).x() << "   " << (_vec[index] + prop.getPos()).y() << std::endl;
	return _vec[index] + prop.getPos();
}

bool zappy::ai::Help::callback(const std::string &res, Properties &properties)
{
	if (!_answered && res == "ok") {
		_answered = true;
		return true;
	}
	if (!_moving)
		return res == "ok";
	return _arrived ? _wait(res, properties) :
		_mov.moveBack(res, properties);
}

bool zappy::ai::Help::_wait(const std::string &res, zappy::ai::Properties &prop)
{
	if (res == "Elevation underway") {
		return true;
	} else if (res.find("Current level:") != std::string::npos) {
		prop.addLvl();
		prop.setEvolving(false);
		return true;
	}
	return false;
}

void zappy::ai::Help::reset()
{
	_arrived = false;
	_answered = false;
}

bool zappy::ai::Help::handleMessage(zappy::ai::Properties &properties)
{
	return false;
}
