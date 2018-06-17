//
// EPITECH PROJECT, 2018
// CBuffer.hpp
// File description:
//
//

#ifndef CBUFFER_HPP_
# define CBUFFER_HPP_

#include <iostream>

#include "../../include/cbuf.h"

namespace zappy
{
	class CBuffer
	{
	public:
		CBuffer(const size_t size);

		void write(const std::string &);
		std::string read(const size_t);
		~CBuffer();
	private:
		cbuf_t _cb;
	};
}
#endif /* !CBUFFER_HPP_ */
