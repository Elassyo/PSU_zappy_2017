//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestParser.hpp
//

#ifndef PSU_ZAPPY_2017_REQUESTPARSER_HPP
#define PSU_ZAPPY_2017_REQUESTPARSER_HPP

#include <string>
#include <sstream>
#include "Inventory.hpp"

namespace zappy
{
	class RequestParser
	{
	public:
		RequestParser();
		~RequestParser() = default;

		bool parseBool(const std::string &);
		uint8_t parseValue(const std::string &);
		bool isDead(const std::string &);
		ai::Inventory parseInventory(const std::string &);
	private:
		std::map<zappy::ai::Item, size_t> _itemNbr;
		std::map<std::string, zappy::ai::Item> _strItem;
	};
}

#endif /* PSU_ZAPPY_2017_REQUESTPARSER_HPP */