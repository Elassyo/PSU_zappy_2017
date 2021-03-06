/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Properties.hpp
*/

#ifndef PSU_ZAPPY_2017_PROPERTIES_HPP
	#define PSU_ZAPPY_2017_PROPERTIES_HPP

	#include <iostream>
	#include "Vertex.hpp"
	#include "Inventory.hpp"
	#include "Memory.hpp"
	#include "Vision.hpp"

namespace zappy {
	namespace ai {
		class Properties {
		public:
			Properties();

			void moveForward();
			void turnRight();
			void turnLeft();
			void setTarget(const VertexS &);
			void setNeed(Item);
			void addLookingFor(Item);
			void pickLookingFor(Item);
			void setLookingFor(const std::vector<Item> &);
			void addLvl();
			void setFood(uint amount);
			void addItem(Item);
			void dropItem(Item);
			std::vector<Item> diff() const;
			void setVision(const Vision &);
			void setEvolving(bool b);
			void kill();
			void setMsg(const std::string &, uint8_t);
			void setMsg(std::pair<std::string, uint8_t>);



			VertexS getPos() const;
			Direction getDir() const;
			bool isAlive() const;
			const VertexS &getTarget() const;
			uint8_t getLvl() const;
			uint getFood() const;
			uint getMinFood() const;
			size_t nbrItem(Item item) const;
			Item getNeed() const;
			const std::vector<Item> &getLookingFor() const;
			const Inventory &getLvlInventory(uint8_t lvl) const;
			uint8_t getLvlPlayers(uint8_t lvl) const;
			const Vision &getVision() const;
			bool isEvolving() const;
			std::pair<uint8_t, std::string> getMsg() const;

		private:
			VertexS _pos;
			Direction _dir;
			VertexS _target;
			bool _alive;
			uint8_t _lvl;
			uint _food;
			uint _minFood;
			Inventory _inventory;
			Item _need;
			std::vector<Item> _lookingFor;
			const std::vector<Inventory> _lvlStuff;
			const std::vector<uint8_t > _lvlplayers;
			Memory _memory;
			Vision _vision;
			bool _isEvolving;
			std::string _msg;
			uint8_t _fromMsg;
		};
	}
}

#endif /* PSU_ZAPPY_2017_PROPERTIES_HPP */