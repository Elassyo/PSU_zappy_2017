/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** LookFor.hpp
*/

#ifndef PSU_ZAPPY_2017_LOOKFOR_HPP
	#define PSU_ZAPPY_2017_LOOKFOR_HPP

	#include "IBehavior.hpp"
	#include "../RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		class LookFor : public virtual IBehavior {
		public:
			LookFor(const RequestConstructor &);

			std::string act() override;
			bool callback(const std::string &string) override;
		private:
			std::string _expected;
			const RequestConstructor &_reqConst;
		};
	}
}

#endif /* PSU_ZAPPY_2017_LOOKFOR_HPP */