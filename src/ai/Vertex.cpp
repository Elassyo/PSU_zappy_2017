//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Vertex.cpp
//

#include "Vertex.hpp"

template <typename T>
zappy::Vertex<T>::Vertex() :
	_x(0), _y(0)
{
}

template <typename T>
zappy::Vertex<T>::Vertex(T x, T y) :
	_x(x), _y(y)
{
}

template <typename T>
zappy::Vertex<T>::Vertex(const Vertex<T> &cpy) :
	_x(cpy.x()), _y(cpy.y())
{
}

template <typename T>
T zappy::Vertex<T>::x() const
{
	return _x;
}

template <typename T>
T zappy::Vertex<T>::y() const
{
	return _y;
}

template <typename T>
T &zappy::Vertex<T>::rx()
{
	return _x;
}

template <typename T>
T &zappy::Vertex<T>::ry()
{
	return _y;
}

template <typename T>
zappy::Vertex<T>& zappy::Vertex<T>::operator=(const Vertex<T> &other)
{
	this->_x = other.x();
	this->_y = other.y();
	return *this;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator+(const Vertex<T> &other) const
{
	zappy::Vertex<T> res(*this);

	res._x += other.x();
	res._y += other.y();
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator-(const Vertex<T> &other) const
{
	zappy::Vertex<T> res(*this);

	res._x -= other.x();
	res._y -= other.y();
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator/(const Vertex<T> &other) const
{
	zappy::Vertex<T> res(*this);

	res._x /= other.x();
	res._y /= other.y();
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator*(const Vertex<T> &other) const
{
	zappy::Vertex<T> res(*this);

	res._x *= other.x();
	res._y *= other.y();
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator+(T other) const
{
	zappy::Vertex<T> res(*this);

	res._x += other;
	res._y += other;
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator-(T other) const
{
	zappy::Vertex<T> res(*this);

	res._x -= other;
	res._y -= other;
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator*(T other) const
{
	zappy::Vertex<T> res(*this);

	res._x *= other;
	res._y *= other;
	return res;
}

template <typename T>
zappy::Vertex<T> zappy::Vertex<T>::operator/(T other) const
{
	zappy::Vertex<T> res(*this);

	res._x /= other;
	res._y /= other;
	return res;
}

template class zappy::Vertex<int>;
template class zappy::Vertex<size_t>;
template class zappy::Vertex<float>;
template class zappy::Vertex<double>;
