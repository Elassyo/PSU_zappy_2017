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
			enum HelpState {
				HEAR,
				WALK,
				ARRIVED
			};
		public:
			explicit Help(const RequestConstructor &);

			std::string act(Properties &properties) override;
			bool callback(const std::string &string, Properties &properties) override;
			bool handleMessage(Properties &properties) override;
			void reset() override;
		private:

			bool _wait(const std::string &res, Properties &prop);
			VertexS _calcPos(Properties &prop, uint8_t dir);

			std::string _walk(Properties &prp);
			std::string _hear(Properties &prp);
			std::string _arrived(Properties &prp);

			bool _walkBack(const std::string &, Properties &prp);
			bool _hearBack(const std::string &, Properties &prp);
			bool _arrivedBack(const std::string &, Properties &prp);

			const RequestConstructor &_reqConst;
			std::vector<VertexS> _vec;
			Movement _mov;
			VertexS _lastCallPos;
			VertexS _toAdd;
			bool _answered;
			bool _evlLaunched;
			bool _xDone;
			uint8_t _lastHeared;
			HelpState _helpState;
		};
	}
}

#endif /* PSU_ZAPPY_2017_HELP_HPP */