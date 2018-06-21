//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestConstructor.cpp
//

#include "RequestConstructor.hpp"

zappy::RequestConstructor::RequestConstructor() :
	_itemStr({
			 {ai::Item::FOOD, "food"},
			 {ai::Item::LINEMATE, "linemate"},
			 {ai::Item::DERAUMERE, "deraumere"},
			 {ai::Item::SIBUR, "sibur"},
			 {ai::Item::MENDIANE, "mendiane"},
			 {ai::Item::PHIRAS, "phiras"},
			 {ai::Item::THYSTAME, "thystame"}})
{
}

std::string zappy::RequestConstructor::moveForward() const
{
	return "forward\n";
}

std::string zappy::RequestConstructor::turnLeft() const
{
	return "left\n";
}

std::string zappy::RequestConstructor::turnRight() const
{
	return "right\n";
}

std::string zappy::RequestConstructor::look() const
{
	return "Look\n";
}

std::string zappy::RequestConstructor::inventory() const
{
	return "Inventory\n";
}

std::string zappy::RequestConstructor::broadcast(std::string text) const
{
	return "broadcast " + text + "\n";
}

std::string zappy::RequestConstructor::connectNbr() const
{
	return "connect_nbr\n";
}

std::string zappy::RequestConstructor::fork() const
{
	return "fork\n";
}

std::string zappy::RequestConstructor::eject() const
{
	return "eject\n";
}

std::string zappy::RequestConstructor::takeObject(zappy::ai::Item item) const
{
	return "take " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::setObject(zappy::ai::Item item) const
{
	return "set " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::incantation() const
{
	return "incantation\n";
}
