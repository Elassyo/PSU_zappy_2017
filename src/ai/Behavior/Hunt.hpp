/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Hunt.hpp
*/

#ifndef PSU_ZAPPY_2017_HUNT_HPP
	#define PSU_ZAPPY_2017_HUNT_HPP

	#include "../RequestConstructor.hpp"
	#include "../Movement.hpp"
	#include "IBehavior.hpp"

namespace zappy {
	namespace ai {
		class Hunt : public virtual IBehavior {
		public:
			Hunt(const RequestConstructor &rstConst);
			~Hunt() = default;

			std::string act(Properties &properties) override;
			bool callback(const std::string &string,
				      Properties &properties) override;

			bool handleMessage(Properties &properties) override;

			void reset() override;

		private:
			const RequestConstructor &_rstConst;
			Movement _movement;
			bool _initTarget;
			bool _moved;
		};
	}
}

#endif /* PSU_ZAPPY_2017_HUNT_HPP */