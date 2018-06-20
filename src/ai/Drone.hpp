//
// EPITECH PROJECT, 2018
// PSU_zappy_2017
// File description:
// Drone.hpp
//

#ifndef PSU_ZAPPY_2017_DRONE_HPP
	#define PSU_ZAPPY_2017_DRONE_HPP

	#include <vector>
	#include <unordered_map>
	#include <functional>
	#include "Inventory.hpp"
	#include "Memory.hpp"
	#include "Vertex.hpp"
	#include "RequestConstructor.hpp"
	#include "RequestHandler.hpp"
	#include "RequestParser.hpp"


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
			const VertexS &, RequestHandler &);
			~Drone() = default;

			bool live();

		private:

			void _evaluatePriorities();
			bool _canEvolve() const;
			std::vector<Item> _evaluateNeeds() const;

			void handleBroadcast(const std::string &msg);

			bool handleResponse(std::function<bool
				(const std::string &)>);

			void _move(const VertexS &dir);
			void setTarget();
			void _moveForward();
			void _look();
			void _turnRight();
			void _turnLeft();
			bool _take(Item);

			Vertex<size_t> _mapSize;
			const std::string &_team;
			Behavior _behave;


			std::unordered_map<Behavior, std::function<void(void)>>
				_act;
			RequestConstructor _reqConstr;
			RequestParser _reqParser;
			RequestHandler &_reqHandler;
		};
	}
}

#endif /* PSU_ZAPPY_2017_DRONE_HPP */