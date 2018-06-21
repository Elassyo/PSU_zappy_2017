//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Vertex.hpp
//

#ifndef PSU_ZAPPY_2017_VERTEX_HPP
	#define PSU_ZAPPY_2017_VERTEX_HPP

	#include <iostream>

namespace zappy {
	template <class T>
	class Vertex
	{
	public:
		Vertex<T>();
		Vertex<T>(const Vertex<T> &);
		Vertex<T>(T x, T y);
		~Vertex<T>() = default;

		T x() const;
		T y() const;
		T &rx();
		T &ry();
		bool operator==(const Vertex<T> &) const;
		Vertex &operator=(const Vertex<T> &);
		Vertex operator+(const Vertex<T> &) const;
		Vertex operator-(const Vertex<T> &) const;
		Vertex operator*(const Vertex<T> &) const;
		Vertex operator/(const Vertex<T> &) const;
		void operator+=(const Vertex<T> &);
		Vertex operator+(T) const;
		Vertex operator-(T) const;
		Vertex operator*(T) const;
		Vertex operator/(T) const;

	private:
		T _x;
		T _y;
	};

	typedef Vertex<ssize_t> VertexS;
	typedef Vertex<int> VertexI;
	typedef Vertex<float> VertexF;
	typedef Vertex<double> VertexD;

}

#endif /* PSU_ZAPPY_2017_VERTEX_HPP */