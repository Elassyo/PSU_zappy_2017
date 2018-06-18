//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.cpp
//

#include "Drone.hpp"

zappy::ai::Drone::Drone(const zappy::ai::Inventory &inventory, uint8_t team,
const VertexS &mapSize) :
	_pos(0, 0), _mapSize(mapSize), _dir(NORTH), _target(0, 0), _alive(true),
	_lvl(1), _team(team), _inventory(inventory), _need(NONE)
{
}

bool zappy::ai::Drone::live()
{
	while (_alive) {
		_evaluatePriorities();
	}
	return false;
}

void zappy::ai::Drone::_evaluatePriorities()
{
	if (_food <= _minFood) {
		_need = FOOD;
		_behave = LOOKFOR;
	} else if (_canEvolve()) {
		_behave = EVOLVE;
		_need = NONE;
	} else {
		_behave = LOOKFOR;
		_need = _evaluateNeeds();
	}
}

bool zappy::ai::Drone::_canEvolve() const
{
	return false;
}

zappy::ai::Item zappy::ai::Drone::_evaluateNeeds() const
{
	return LINEMATE;
}

void zappy::ai::Drone::_move(const zappy::VertexS &dir)
{
}

void zappy::ai::Drone::_moveForward()
{
	if (_dir % 2 == 0)
		_pos.ry() += _dir == NORTH ? 1 : -1;
	else
		_pos.rx() += _dir == EAST ? 1 : -1;
}

void zappy::ai::Drone::lookFor()
{

}

void zappy::ai::Drone::_look()
{
}

void zappy::ai::Drone::_turnRight()
{
	_dir = (Direction) ((_dir + 1) % MAX);
}

void zappy::ai::Drone::_turnLeft()
{
	_dir = (Direction) (_dir ? _dir - 1 : MAX - 1);
}

bool zappy::ai::Drone::_take(zappy::ai::Item)
{
	return false;
}
