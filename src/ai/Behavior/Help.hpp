/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Help.hpp
*/

#ifndef PSU_ZAPPY_2017_HELP_HPP
	#define PSU_ZAPPY_2017_HELP_HPP

	#include "IBehavior.hpp"
	#include "../Movement.hpp"
	#include "../RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		class Help : public virtual IBehavior {

		public:
			explicit Help(const RequestConstructor &);

			std::string act(Properties &properties) override;
			bool callback(const std::string &string, Properties &properties) override;
			void reset() override;
		private:
			const RequestConstructor &_reqConst;
			std::vector<VertexS> _vec;
			Movement _mov;
			bool _answered;
		};
	}
}

#endif /* PSU_ZAPPY_2017_HELP_HPP */