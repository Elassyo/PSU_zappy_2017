//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.hpp
//

#ifndef PSU_ZAPPY_2017_DRONE_HPP
	#define PSU_ZAPPY_2017_DRONE_HPP

	#include <vector>
	#include <map>
	#include <functional>
	#include <memory>
	#include "RequestHandler.hpp"
	#include "RequestParser.hpp"

	#include "Behavior/Evolve.hpp"
	#include "Behavior/LookFor.hpp"
	#include "Behavior/Help.hpp"

namespace zappy {
	namespace ai {
		enum Behavior {
			WAIT,
			LOOKFOR,
			GATHER,
			EVOLVE,
			EXPLORE,
			HELP
		};

		class Drone {
		public:
			explicit Drone(const std::string &team,
				RequestHandler &);
			~Drone() = default;

			bool live();

		private:

			void _evaluatePriorities();
			bool _canEvolve() const;
			std::vector<Item> _evaluateNeeds() const;

			void handleBroadcast(const std::string &msg);

			bool handleResponse();

			void _move(const VertexS &dir);
			void _look();
			bool _take(Item);

			Properties _properties;
			Vertex<size_t> _mapSize;
			const std::string &_team;
			Behavior _behave;

			std::map<Behavior, std::shared_ptr<IBehavior>> _act;
			RequestConstructor _reqConstr;
			RequestParser _reqParser;
			RequestHandler &_reqHandler;
		};
	}
}

#endif /* PSU_ZAPPY_2017_DRONE_HPP */