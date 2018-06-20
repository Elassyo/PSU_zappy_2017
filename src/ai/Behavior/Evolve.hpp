/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Evolve.hpp
*/

#ifndef PSU_ZAPPY_2017_EVOLVE_HPP
	#define PSU_ZAPPY_2017_EVOLVE_HPP

	#include "IBehavior.hpp"
	#include "../RequestConstructor.hpp"

namespace zappy {
	namespace ai {
		enum EvolveState {
			CALL,
			DROP,
			INCANTE
		};
		class Evolve : public virtual IBehavior {
		public:
			explicit Evolve(const RequestConstructor &);
			std::string act
				(zappy::ai::Properties &properties) override;
			bool callback(const std::string &string,
				Properties &properties) override;
			void reset() override;

		private:
			std::string _call();
			std::string _drop();
			std::string _incante();
			const RequestConstructor &_reqConst;
			EvolveState _evlState;
			Inventory _toPut;
		};
	}
}

#endif /* PSU_ZAPPY_2017_EVOLVE_HPP */