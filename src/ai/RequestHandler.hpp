//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// RequestHandler.hpp
//

#ifndef PSU_ZAPPY_2017_REQUESTHANDLER_HPP
	#define PSU_ZAPPY_2017_REQUESTHANDLER_HPP

	#include <string>
	#include "Exception/Exception.hpp"
	#include "../../include/tcp.h"

namespace zappy {
	class RequestHandler {
	public:
		RequestHandler(const std::string &hostname, uint16_t port);
		~RequestHandler();

		void send(const std::string &);
		std::string recv();
		void fetch();
		const std::string &getLastMessage();
	private:
		std::string _lastMsg;
		tcp_client_t _client;
	};
}

#endif /* PSU_ZAPPY_2017_REQUESTHANDLER_HPP */