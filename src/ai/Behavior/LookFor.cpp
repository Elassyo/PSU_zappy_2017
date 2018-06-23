#include <string>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** LookFor.cpp
*/

#include "LookFor.hpp"
#include "../Properties.hpp"
#include "../Exception/Exception.hpp"

zappy::ai::LookFor::LookFor(const zappy::RequestConstructor &requestConstructor)
	: _lookState(LOOK), _reqConst(requestConstructor), _item(NONE),
	  _cor({{NORTH, std::bind(&LookFor::_fromNorth, this, std::placeholders::_1)},
		{SOUTH, std::bind(&LookFor::_fromSouth, this, std::placeholders::_1)},
		{EAST, std::bind(&LookFor::_fromEast, this, std::placeholders::_1)},
		{WEST, std::bind(&LookFor::_fromWest, this, std::placeholders::_1)}})
{
}

std::string zappy::ai::LookFor::act(zappy::ai::Properties &properties)
{
	switch (_lookState) {
	case LOOK:
		return _look();
	case GO:
		return _go(properties);
	case TAKE:
		return _gather();
	}
	return "";
}

bool zappy::ai::LookFor::callback(const std::string &string, Properties &properties)
{
	std::cout << "callback" << std::endl;
	switch (_lookState) {
	case LOOK:
		return _lookBack(string, properties);
	case GO:
		return _goBack(string, properties);
	case TAKE:
		return _gatherBack(string, properties);
	}
	return false;
}

void zappy::ai::LookFor::reset()
{
	_lookState = LOOK;
}

std::string zappy::ai::LookFor::_look()
{
	return _reqConst.look();
}

std::string zappy::ai::LookFor::_go(Properties &prop)
{
	if (prop.getPos() == prop.getTarget()) {
		_lookState = _item == NONE ? LOOK : TAKE;
		_lastAction = "";
		return "";
	}
	return _move(prop);
}

std::string zappy::ai::LookFor::_move(zappy::ai::Properties &properties)
{
	std::string s = _cor[properties.getDir()](properties);
	if (s.empty()) {
		_lastAction = "move";
		return _reqConst.moveForward();
	}
	_lastAction = s;
	return s;
}

std::string zappy::ai::LookFor::_fromNorth(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
			_reqConst.turnRight() : _reqConst.turnLeft();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       "" : _reqConst.turnRight();
	}
}

std::string zappy::ai::LookFor::_fromSouth(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
		       _reqConst.turnLeft() : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() < prp.getPos().y() ?
		       "" : _reqConst.turnRight();
	}
}

std::string zappy::ai::LookFor::_fromEast(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() > prp.getPos().x() ?
		       "" : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       _reqConst.turnLeft() : _reqConst.turnRight();
	}

}

std::string zappy::ai::LookFor::_fromWest(zappy::ai::Properties &prp)
{
	if (prp.getTarget().x() != prp.getPos().x()) {
		return prp.getTarget().x() < prp.getPos().x() ?
		       "" : _reqConst.turnRight();
	}
	else {
		return prp.getTarget().y() > prp.getPos().y() ?
		       _reqConst.turnRight() : _reqConst.turnLeft();
	}

}

std::string zappy::ai::LookFor::_gather()
{
	if (_item != NONE)
		return _reqConst.takeObject(_item);
	throw Exception("LookFor", "No Item to gather");
}

bool zappy::ai::LookFor::_lookBack(const std::string &res, Properties &prop)
{
	auto lf = prop.getLookingFor();
	try {
		Vision vision(res);
		_item = prop.getNeed();
		bool saw = false;
		if (_item != NONE)
			saw = sawObject(_item, prop, vision);
		else
			saw = sawObject(lf, prop, vision);
		std::cout << "PObject saw" << std::endl;
		if (!saw) {
			std::cout << "random target" << std::endl;
			prop.setTarget(prop.getPos() + random() % 5);
			_item = NONE;
		}
	} catch (const Exception &e) {
		std::cerr <<  e.where() << e.what() << std::endl;
		return false;
	}
	_lookState = GO;
	return true;
}

bool zappy::ai::LookFor::sawObject(const std::vector<zappy::ai::Item> &lf,
					Properties &prop, Vision &vision)
{
	for (size_t i = 0; i < prop.getLookingFor().size(); i++)
		if (vision.seeObject(lf[i])) {
			std::cout << "OBJ Seen" << std::endl;
			prop.setTarget(vision.getObject(lf[i],
							prop.getPos(),
							prop.getDir()));
			_lookState = GO;
			_item = lf[i];
			return true;
		}
	return false;
}

bool zappy::ai::LookFor::sawObject(zappy::ai::Item need, Properties &prop,
					Vision &vision)
{
	if (vision.seeObject(need)) {
		std::cout << "OBJ Seen" << std::endl;
		prop.setTarget(vision.getObject(need,
						prop.getPos(),
						prop.getDir()));
		_lookState = GO;
		_item = need;
		return true;
	}
	return false;
}

bool zappy::ai::LookFor::_goBack(const std::string &res, Properties &prop)
{
	if (res != "ok")
		return false;
	if (_lastAction == "move")
		prop.moveForward();
	else if (_lastAction == _reqConst.turnLeft())
		prop.turnLeft();
	else
		prop.turnRight();
	return true;
}

bool zappy::ai::LookFor::_gatherBack(const std::string &res, Properties &prop)
{
	if (res == "ok") {
		if (_item != NONE) {
			prop.addItem(_item);
			prop.pickLookingFor(_item);
		}
		prop.setTarget(prop.getPos() + random() % 5);
		_item = NONE;
	} else if (res == "ko") {
		_lookState = LOOK;
	} else
		return false;
	_lookState = GO;
	return true;
}