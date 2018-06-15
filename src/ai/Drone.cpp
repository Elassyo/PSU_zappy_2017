//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.cpp
//

#include "Drone.hpp"

zappy::ai::Drone::Drone(zappy::Vertex<size_t> pos) :
	_pos(pos), _target(0, 0), _lvl(1)
{
}

