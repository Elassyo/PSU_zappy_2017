/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** LookFor.hpp
*/

#ifndef PSU_ZAPPY_2017_LOOKFOR_HPP
	#define PSU_ZAPPY_2017_LOOKFOR_HPP

	#include <map>
	#include <functional>
	#include "IBehavior.hpp"
	#include "../Movement.hpp"

namespace zappy {
	namespace ai {
		enum LookForState {
			LOOK,
			GO,
			TAKE
		};
		class LookFor : public virtual IBehavior {
		public:
			explicit LookFor(const RequestConstructor &);

			std::string
			act(zappy::ai::Properties &properties) override;
			bool callback(const std::string &string,
				Properties &properties) override;

			bool handleMessage(Properties &properties) override;

			void reset() override;

		private:
			std::string _look();
			std::string _go(Properties &prop);
			std::string _gather();

			bool _lookBack(const std::string &res, Properties &prop);
			bool _goBack(const std::string &res, Properties &prop);
			bool _gatherBack(const std::string &res, Properties &prop);

			bool sawObject(const std::vector<Item> &, Properties &, Vision &);
			bool sawObject(Item, Properties &, Vision &);

			LookForState _lookState;
			const RequestConstructor &_reqConst;
			Item _item;
			Movement _mov;
		};
	}
}

#endif /* PSU_ZAPPY_2017_LOOKFOR_HPP */