/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Alien
*/

#ifndef ALIEN_HPP_
#define ALIEN_HPP_

#include "../../server/game_engine/include/Entities/Enemy.hpp"
#include "../../server/game_engine/include/Vector.hpp"
#include "../../server/game_engine/include/EntitiesEnum.hpp"
#include <vector>
#include <memory>

namespace enemies {
    class Alien : public game_engine::Enemy {
        public:
            Alien(game_engine::Vector position, int id);
            ~Alien();
            void pathEnemy();

        protected:
        private:
    };
}

#endif /* !ALIEN_HPP_ */
