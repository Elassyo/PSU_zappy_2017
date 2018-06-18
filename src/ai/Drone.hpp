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
	#include "Vertex.hpp"
#include "RequestConstructor.hpp"


namespace zappy {
	namespace ai {
		enum Direction {
			NORTH = 0,
			EAST = 1,
			SOUTH = 2,
			WEST = 3,
			MAX = 4
		};
		enum Behavior {
			NONE = 0,
			WAIT,
			LOOKFOR,
			GATHER,
			EVOLVE,
			EXPLORE
		};
		class Drone {
		public:
			explicit Drone(const Inventory &, uint8_t team,
			const VertexS &);
			~Drone() = default;

			bool live();

		private:

			void _evaluatePriorities();
			bool _canEvolve() const;
			Item _evaluateNeeds() const;

			void _lookFor();
			void _explore();
			void _gatherResources();
			void _evolve();
			void _wait();

			void _move(const VertexS &dir);
			void _moveForward();
			void _look();
			void _turnRight();
			void _turnLeft();
			bool _take(Item);

			Vertex<size_t> _pos;
			Vertex<size_t> _mapSize;
			Direction _dir;
			Vertex<size_t> _target;
			bool _alive;
			uint8_t _lvl;
			uint8_t _team;
			Behavior _behave;

			uint _food;
			uint _minFood;
			Inventory _inventory;
			Item _need;
			std::vector<Item> _lookingFor;
			const std::vector<Inventory> _lvlStuff;
			std::multimap<Item, VertexS> _memory;
			std::unordered_map<Behavior, std::function<void(void)>>
				_act;
			RequestConstructor _reqConstr;
		};
	}
}

#endif /* PSU_ZAPPY_2017_DRONE_HPP */