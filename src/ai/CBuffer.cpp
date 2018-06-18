//
// EPITECH PROJECT, 2018
// CBuffer.cpp
// File description:
//
//

#include "CBuffer.hpp"
#include "Exception/Exception.hpp"

zappy::CBuffer::CBuffer(const size_t size)
{
	cbuf_create(&this->_cb, size);
}

zappy::CBuffer::~CBuffer()
{
	cbuf_destroy(&this->_cb);
}

std::string zappy::CBuffer::read(const size_t n)
{
	char *buffer = new char[n + 1];

	if (cbuf_read(&_cb, (void *)buffer, n) == 0)
		throw zappy::Exception("CBuffer", "Can't read cbuf");
	std::string s(buffer);
	delete [] buffer;
	return s;
}

void zappy::CBuffer::write(const std::string &toWrite)
{
	if (cbuf_write(&_cb, (void*)toWrite.c_str(), toWrite.length()) == 0)
		throw zappy::Exception("CBuffer", "Can't write cbuf");
}
