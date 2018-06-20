/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Evolve.hpp
*/

#ifndef PSU_ZAPPY_2017_EVOLVE_HPP
	#define PSU_ZAPPY_2017_EVOLVE_HPP

	#include "IBehavior.hpp"

namespace zappy {
	namespace ai {
		class Evolve : public virtual IBehavior {
			explicit Evolve()  = default;

		public:
			std::string act() override;

			bool callback(const std::string &string) override;

			void reset() override;
		};
	}
}

#endif /* PSU_ZAPPY_2017_EVOLVE_HPP */