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
	_answered(false)
{
}

std::string zappy::ai::Help::act(Properties &properties)
{
	auto pair = properties.getMsg();
	if (!_answered) {
		_answered = true;
		return _reqConst.broadcast("GOERK");
	}
	if (pair.first == 0)
		return "";
	properties.setTarget(properties.getPos() + _vec[pair.first - 1]);
	 return _mov.move(properties);
}

bool zappy::ai::Help::callback(const std::string &res, Properties &properties)
{
	return _mov.moveBack(res, properties);
}

void zappy::ai::Help::reset()
{
}
