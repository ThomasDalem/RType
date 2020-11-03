/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include <iostream>
#include <map>
#include <memory>
#include "Components/Transform.hpp"
#include "Components/Collision.hpp"
#include "EntitiesEnum.hpp"

namespace game_engine
{
    class CollisionSystem {
        public:
            CollisionSystem();
            ~CollisionSystem();
            void collisionSystem(std::map<EntitiesType, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>>> map);
            bool checkCollision(std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect1, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect2);

        protected:
        private:
    };
} // namespace game_engine

#endif /* !COLLISIONSYSTEM_HPP_ */
