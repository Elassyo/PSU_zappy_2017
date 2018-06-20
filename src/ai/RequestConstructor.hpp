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

		std::string moveForward() const;
		std::string turnLeft() const;
		std::string turnRight() const;

		std::string look() const;
		std::string inventory() const;
		std::string broadcast(std::string text) const;

		std::string connectNbr() const;
		std::string fork() const;
		std::string eject() const;

		std::string takeObject(zappy::ai::Item item) const;
		std::string setObject(zappy::ai::Item item) const;
		std::string incantation() const;

	private:
		std::map<zappy::ai::Item, std::string> _itemStr;
	};
} // namespace zappy

#endif /* PSU_ZAPPY_2017_REQUESTCONSTRUCTOR_HPP */