//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestHandler.cpp
//

#include <iostream>
#include "RequestHandler.hpp"

zappy::RequestHandler::RequestHandler
	(const std::string &hostname, uint16_t port) :
	_file(nullptr)
{
	if (!tcp_client_connect(&_client, hostname.c_str(), port))
		throw Exception("RequestHandler", "Can't connect to server");
	_file = fdopen(_client.conn.sock.fd, "rw");
	if (_file == nullptr)
		throw Exception("RequestHandler", "fdopen failed");
}

zappy::RequestHandler::~RequestHandler()
{
	tcp_client_close(&_client);
}

void zappy::RequestHandler::send(const std::string &msg)
{
	size_t len = msg.length();
	if (tcp_conn_write(&_client.conn, msg.c_str(), len) != len)
		throw Exception("RequestHandler", "msg not send correctly");
}

void zappy::RequestHandler::fetch()
{
}

std::string zappy::RequestHandler::recv()
{
	char *buffer = nullptr;
	size_t l = 0;
	if (getline(&buffer, &l, _file) == -1)
		throw Exception("RequestHandler", "Error while receving msg");
	std::string s(buffer);
	free(buffer);
	s.pop_back();
	return s;
}

const std::string &zappy::RequestHandler::getLastMessage()
{
	return _lastMsg;
}
