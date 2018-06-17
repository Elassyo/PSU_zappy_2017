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

std::string zappy::RequestConstructor::moveForward()
{
	return "forward\n";
}

std::string zappy::RequestConstructor::turnLeft()
{
	return "left\n";
}

std::string zappy::RequestConstructor::turnRight()
{
	return "right\n";
}

std::string zappy::RequestConstructor::look()
{
	return "look\n";
}

std::string zappy::RequestConstructor::inventory()
{
	return "inventory\n";
}

std::string zappy::RequestConstructor::broadcast(std::string text)
{
	return "broadcast " + text + "\n";
}

std::string zappy::RequestConstructor::connectNbr()
{
	return "connect_nbr\n";
}

std::string zappy::RequestConstructor::fork()
{
	return "fork\n";
}

std::string zappy::RequestConstructor::eject()
{
	return "eject\n";
}

std::string zappy::RequestConstructor::takeObject(zappy::ai::Item item)
{
	return "take " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::setObject(zappy::ai::Item item)
{
	return "set " + this->_itemStr.at(item) + "\n";
}

std::string zappy::RequestConstructor::incantation()
{
	return "incantation\n";
}

int testRequestMain()
{
	zappy::RequestConstructor rc;

	std::cout << rc.moveForward();
	std::cout << rc.turnLeft();
	std::cout << rc.turnRight();

	std::cout << rc.look();
	std::cout << rc.inventory();
	std::cout << rc.broadcast("Bonjour, moi c'est jaka");

	std::cout << rc.connectNbr();
	std::cout << rc.fork();
	std::cout << rc.eject();

	std::cout << rc.takeObject(zappy::ai::Item::FOOD);
	std::cout << rc.setObject(zappy::ai::Item::LINEMATE);
	std::cout << rc.incantation();

	return 0;
}