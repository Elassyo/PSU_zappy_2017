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
	_lvl(1), _team(team), _behave(Behavior::NONE), _food(10), _minFood(3),
	_inventory(inventory), _need(NONE),
	_lvlStuff({Inventory(1, 0, 0, 0, 0, 0), Inventory(1, 1, 1, 0, 0, 0),
		  Inventory(2, 0, 1, 0, 2, 0), Inventory(1, 1, 2, 0, 1, 0),
		  Inventory(1, 2, 1, 3, 0, 0), Inventory(1, 2, 3, 0, 1, 0),
		  Inventory(2, 2, 2, 2, 2, 1)}),
	_act({	{EVOLVE, _evolve},
		{WAIT, _wait},
		{LOOKFOR, _lookingFor},
		{EXPLORE, _explore}})
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

void zappy::ai::Drone::_explore()
{
}

void zappy::ai::Drone::_gatherResources()
{
}

void zappy::ai::Drone::_evolve()
{
}

void zappy::ai::Drone::_wait()
{
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
	_reqConstr.moveForward();
}

void zappy::ai::Drone::_lookFor()
{
}

void zappy::ai::Drone::_look()
{
	_reqConstr.look();
}

void zappy::ai::Drone::_turnRight()
{
	_dir = (Direction) ((_dir + 1) % MAX);
	_reqConstr.turnRight();
}

void zappy::ai::Drone::_turnLeft()
{
	_dir = (Direction) (_dir ? _dir - 1 : MAX - 1);
	_reqConstr.turnLeft();
}

bool zappy::ai::Drone::_take(zappy::ai::Item)
{
	_reqConstr.takeObject(Item::FOOD);
	return false;
}
