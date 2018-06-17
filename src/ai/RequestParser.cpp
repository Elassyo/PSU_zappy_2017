//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestParser.cpp
//

#include "RequestParser.hpp"
#include "Exception/Exception.hpp"

zappy::RequestParser::RequestParser() :
_itemNbr({
		 {ai::Item::FOOD, 0},
		 {ai::Item::LINEMATE, 0},
		 {ai::Item::DERAUMERE, 0},
		 {ai::Item::SIBUR, 0},
		 {ai::Item::MENDIANE, 0},
		 {ai::Item::PHIRAS, 0},
		 {ai::Item::THYSTAME, 0}}),
_strItem({
		 {"food", ai::Item::FOOD},
		 {"linemate", ai::Item::LINEMATE},
		 {"deraumere", ai::Item::DERAUMERE},
		 {"sibur", ai::Item::SIBUR},
		 {"mendiane", ai::Item::MENDIANE},
		 {"phiras", ai::Item::PHIRAS},
		 {"thystame", ai::Item::THYSTAME},
})
{}

bool zappy::RequestParser::parseBool(const std::string &request)
{
	return request == "ok";
}

uint8_t zappy::RequestParser::parseValue(const std::string &request)
{
	std::stringstream ss(request);
	std::string token;

	while (std::getline(ss, token, ' '));
	return static_cast<uint8_t>(std::stoi(token));
}

bool zappy::RequestParser::isDead(const std::string &request)
{
	return request == "dead";
}

zappy::ai::Inventory zappy::RequestParser::parseInventory(const std::string &request)
{
	if (request[0] != '[' && request[request.length() - 1] != ']')
		throw Exception("RequestParser", "Request malformed");

	std::stringstream ss(request);
	std::string token;
	std::string strItem;
	size_t nbr;

	while (std::getline(ss, token, ',')) {
		std::stringstream st(token);
		st >> strItem >> nbr;
		this->_itemNbr[this->_strItem[strItem]] = nbr;
	}
	return ai::Inventory(this->_itemNbr);
}