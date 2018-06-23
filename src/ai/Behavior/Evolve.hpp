/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Evolve.hpp
*/

#ifndef PSU_ZAPPY_2017_EVOLVE_HPP
	#define PSU_ZAPPY_2017_EVOLVE_HPP

	#include "IBehavior.hpp"
	#include "../Helper.hpp"
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
			std::string _call(Properties &prp);
			std::string _drop();
			std::string _incante(Properties &properties);

			bool _callBack(const std::string &res, Properties &prp);
			bool _dropBack(const std::string &res, Properties &prp);
			bool _incanteBack(const std::string &res, Properties &);

			const RequestConstructor &_reqConst;
			EvolveState _evlState;
			std::vector<Item> _toPut;
			Tile _place;
			bool _isIncantating;
			bool _checked;
			bool _isLooking;
			int _connectNbr;
			int _resReceved;
			int _plReady;
			bool _triedCall;
			size_t _loop;

			std::string _lastReq;
		};
	}
}

#endif /* PSU_ZAPPY_2017_EVOLVE_HPP */