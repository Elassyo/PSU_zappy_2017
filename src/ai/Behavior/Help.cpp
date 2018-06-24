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
	_answered(false), _arrived(false), _moved(false)
{
}

std::string zappy::ai::Help::act(Properties &properties)
{
	std::cout << "HELLLLLLPPPPPPIIIINNNGGGG " << std::endl;
	auto pair = properties.getMsg();
	if (!_answered) {
		_moved = false;
		return _reqConst.broadcast("GOERK");
	}
	if (!pair.second.empty()) {
		_lastCallPos = _calcPos(properties, pair.first);
		properties.setMsg(std::make_pair("", 0));
	}
	if (pair.first == 0 && !pair.second.empty()) {
		_arrived = true;
		properties.setEvolving(true);
		_moved = false;
		return _reqConst.broadcast("HERE");
	}
	properties.setTarget(_lastCallPos);
	std::cout << (int) properties.getDir() << std::endl;
	_moved = true;
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
	if (_moved)
		_mov.moveBack(res, properties);
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
