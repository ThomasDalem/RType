/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** BattleShip
*/

#ifndef BATTLESHIP_HPP_
#define BATTLESHIP_HPP_

#include "../../server/game_engine/include/Entities/Enemy.hpp"
#include "../../server/game_engine/include/Vector.hpp"
#include <vector>
#include <memory>

namespace enemies {
    class BattleShip : public game_engine::Enemy {
        public:
            BattleShip(game_engine::Vector position);
            ~BattleShip();
            void pathEnemy();

        protected:
        private:
    };
}

#endif /* !BATTLESHIP_HPP_ */
