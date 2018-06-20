/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** IBehavior.hpp
*/

#ifndef PSU_ZAPPY_2017_IBEHAVIOR_HPP
	#define PSU_ZAPPY_2017_IBEHAVIOR_HPP

	#include <string>
	#include "../Properties.hpp"

namespace zappy {
	namespace ai {
		class IBehavior {
		public:
			~IBehavior() = default;

			virtual std::string act(Properties &properties) = 0;
			virtual bool callback(const std::string &,
					Properties &properties) = 0;
			virtual void reset() = 0;
		};
	}
}

#endif /* PSU_ZAPPY_2017_IBEHAVIOR_HPP */