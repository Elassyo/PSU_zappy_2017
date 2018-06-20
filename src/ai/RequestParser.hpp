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

		bool isEvent(const std::string &) const;
		bool parseBool(const std::string &) const;
		uint8_t parseValue(const std::string &) const;
		bool isDead(const std::string &) const;
		ai::Inventory parseInventory(const std::string &);
	private:
		std::map<zappy::ai::Item, size_t> _itemNbr;
		const std::map<std::string, zappy::ai::Item> _strItem;
	};
}

#endif /* PSU_ZAPPY_2017_REQUESTPARSER_HPP */