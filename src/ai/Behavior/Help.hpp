/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Help.hpp
*/

#ifndef PSU_ZAPPY_2017_HELP_HPP
	#define PSU_ZAPPY_2017_HELP_HPP

	#include "IBehavior.hpp"
	#include "../RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		class Help : public virtual IBehavior {

		public:
			Help(const RequestConstructor &);

			std::string act(Properties &properties) override;
			bool callback(const std::string &string, Properties &properties) override;
			void reset() override;

		private:
			const RequestConstructor &_reqConst;
		};
	}
}

#endif /* PSU_ZAPPY_2017_HELP_HPP */