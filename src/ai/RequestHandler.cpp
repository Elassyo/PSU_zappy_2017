//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestHandler.cpp
//

#include "RequestHandler.hpp"

zappy::RequestHandler::RequestHandler
	(const std::string &hostname, uint16_t port)
{
	if (!tcp_client_connect(&_client, hostname.c_str(), port))
		throw Exception("RequestHandler", "Can't connect to server");
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

std::string zappy::RequestHandler::recv()
{
	char buffer[512];
	if (tcp_conn_getline(&_client.conn, buffer, 512, '\n'))
		throw Exception("RequestHandler", "Error while receving msg");
	return std::string(buffer);
}
