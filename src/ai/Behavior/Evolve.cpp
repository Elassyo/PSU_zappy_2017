/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Evolve.cpp
*/

#include "Evolve.hpp"
#include "../Exception/Exception.hpp"

zappy::ai::Evolve::Evolve(const zappy::RequestConstructor &rq) :
	_reqConst(rq), _evlState(DROP), _place(""),
	_isIncantating(false), _checked(false), _isLooking(false),
	_connectNbr(0), _resRecieved(0), _plReady(1), _triedCall(false)
{
}

std::string zappy::ai::Evolve::act(zappy::ai::Properties &properties)
{
	properties.setEvolving(true);
	if (_toPut.empty() && !_checked)
		_toPut = properties.getLvlInventory
			(properties.getLvl()).toVector();
	switch (_evlState) {
	case CALL:
		return _call(properties);
	case DROP:
		return _drop();
	case INCANTE:
		return _incante();
	}
	throw Exception("Evolve", "State not set");
}

bool zappy::ai::Evolve::callback(const std::string &res,
				Properties &properties)
{
	switch (_evlState) {
	case DROP:
		return _dropBack(res, properties);
	case CALL:
		return _callBack(res, properties);
	case INCANTE:
		return _incanteBack(res, properties);
	}
	throw Exception("Evolve", "Evolve callback state not set");
}

void zappy::ai::Evolve::reset()
{
	_isIncantating = false;
	_isLooking = false;
	_checked = false;
	_toPut.clear();
	_evlState = DROP;
	_place = Tile("");
	_resRecieved = 0;
	_plReady = 1;
	_connectNbr = 0;
}

std::string zappy::ai::Evolve::_call(Properties &prp)
{
	std::string s;
	if (_plReady == prp.getLvlPlayers(prp.getLvl())) {
		_evlState = INCANTE;
		_lastReq = "";
		return "";
	}
	if (_connectNbr == 0 && _lastReq != _reqConst.connectNbr())
		s =  _reqConst.connectNbr();
	else if (_connectNbr >= prp.getLvlPlayers(prp.getLvl())
		&& !_triedCall) {
		s = _reqConst.broadcast(
			"KREOG " + std::to_string(prp.getLvl()));
		_triedCall = true;
	} else {

	}
	return s;
}

std::string zappy::ai::Evolve::_drop()
{
	if (!_checked) {
		_isLooking = true;
		return _reqConst.look();
	}
	if (!_place.empty()) {
		std::cout << "EVOLVE PLACE NOT EMPTY" << std::endl;
		_checked = false;
		return _reqConst.takeObject(_place.getItem());
	}
	if (_toPut.empty()) {
		_evlState = CALL;
		return "";
	}
	return _reqConst.setObject(_toPut[0]);
}

std::string zappy::ai::Evolve::_incante()
{
	if (!_isIncantating)
		return _reqConst.incantation();
	return "wait";
}

bool
zappy::ai::Evolve::_callBack(const std::string &res, zappy::ai::Properties &prp)
{
	if (res == "GOERK") {

	} else if (Helper::isNumber(res))  {
		_connectNbr = std::stoi(res);
		return true;
	}
	return res == "ok";
}

bool
zappy::ai::Evolve::_dropBack(const std::string &res, zappy::ai::Properties &prp)
{
	if (!_checked && _isLooking) {
		try {
			Vision vis(res);
			_place = vis.getTile(0);
			_checked = true;
			_isLooking = false;
			std::cout << "EVOLVE LOOK DONE" << std::endl;
			return true;
		} catch (const Exception &) {
			return false;
		}
	}
	if (res == "ok") {
		prp.dropItem(*_toPut.begin());
		_toPut.erase(_toPut.begin());
		return true;
	}
	return false;
}

bool
zappy::ai::Evolve::_incanteBack
	(const std::string &res, zappy::ai::Properties &prp)
{
	if (!_isIncantating && res == "Elevation underway") {
		_isIncantating = true;
	} else if (res == "ko")
		reset();
	if (res.find("Current level:") != std::string::npos) {
		std::cout << "LEVEL UP !!!" << std::endl;
		prp.setEvolving(false);
		prp.addLvl();
		reset();
	}
	return true;
}