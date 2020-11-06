/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Trooper
*/

#ifndef TROOPER_HPP_
#define TROOPER_HPP_

#include "../../server/game_engine/include/Entities/Enemy.hpp"
#include "../../server/game_engine/include/Vector.hpp"
#include <vector>
#include <memory>

namespace enemies {
    class Trooper : public game_engine::Enemy {
        public:
            Trooper(game_engine::Vector position);
            ~Trooper();
            void pathEnemy();

        protected:
        private:
    };
}

#endif /* !TROOPER_HPP_ */
