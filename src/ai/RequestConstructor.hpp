//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestConstructor.hpp
//

#ifndef PSU_ZAPPY_2017_REQUESTCONSTRUCTOR_HPP
#define PSU_ZAPPY_2017_REQUESTCONSTRUCTOR_HPP

#include <iostream>
#include <map>
#include "Inventory.hpp"

namespace zappy
{
	class RequestConstructor
	{
  	public:
		RequestConstructor();
		~RequestConstructor() = default;

		std::string moveForward();
		std::string turnLeft();
		std::string turnRight();

		std::string look();
		std::string inventory();
		std::string broadcast(std::string text);

		std::string connectNbr();
		std::string fork();
		std::string eject();

		std::string takeObject(zappy::ai::Item item);
		std::string setObject(zappy::ai::Item item);
		std::string incantation();

	private:
		std::map<zappy::ai::Item, std::string> _itemStr;
	};
} // namespace zappy

#endif /* PSU_ZAPPY_2017_REQUESTCONSTRUCTOR_HPP */