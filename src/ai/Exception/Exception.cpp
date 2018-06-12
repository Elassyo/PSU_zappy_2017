//
// EPITECH PROJECT, 2018
// ai
// File description:
// zappy
//

#include "Exception.hpp"

zappy::Exception::Exception(const std::string &ctx, const std::string &msg) :
	_context(ctx), _message(msg)
{}

const char *zappy::Exception::what() const throw()
{
	return this->_message.c_str();
}

const char *zappy::Exception::where() const throw()
{
	return this->_context.c_str();
}
