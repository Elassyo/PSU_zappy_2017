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
	return "Forward\n";
}

std::string zappy::RequestConstructor::turnLeft() const
{
	return "Left\n";
}

std::string zappy::RequestConstructor::turnRight() const
{
	return "Right\n";
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
	return "Broadcast " + text + "\n";
}

std::string zappy::RequestConstructor::connectNbr() const
{
	return "Connect_nbr\n";
}

std::string zappy::RequestConstructor::fork() const
{
	return "Fork\n";
}

std::string zappy::RequestConstructor::eject() const
{
	return "Eject\n";
}

std::string zappy::RequestConstructor::takeObject(zappy::ai::Item item) const
{
	if (item == zappy::ai::Item::DRONE)
		return "";
	return "Take " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::setObject(zappy::ai::Item item) const
{
	return "Set " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::incantation() const
{
	return "Incantation\n";
}
