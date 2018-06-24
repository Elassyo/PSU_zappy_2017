/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Mean.hpp
*/

#ifndef PSU_ZAPPY_2017_MEAN_HPP
#define PSU_ZAPPY_2017_MEAN_HPP

#include "IBehavior.hpp"
#include "../RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		enum LookForState {
			LOOK,
			GO,
			TAKE
		};
		class Mean : public virtual IBehavior {
		public:
			Mean(const zappy::RequestConstructor &requestConstructor);
			std::string act(Properties &properties) override;
			bool callback(const std::string &string,
				      Properties &properties) override;
			void reset() override;

		private:
			LookForState _lookState;
			RequestConstructor _rqsConst;
		};
	}
}

#endif /* PSU_ZAPPY_2017_MEAN_HPP */