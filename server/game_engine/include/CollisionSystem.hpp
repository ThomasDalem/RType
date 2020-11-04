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
#include "Entities/PowerUp.hpp"
#include "EntitiesEnum.hpp"
#include "Entities/IEntities.hpp"

namespace game_engine
{
    class CollisionSystem {
        public:
            CollisionSystem(std::vector<std::shared_ptr<IEntities>> &player, std::vector<std::shared_ptr<IEntities>> &powerUp, std::vector<std::shared_ptr<IEntities>> &objectAndEnnemy);
            ~CollisionSystem();

            void collisionSystem();
            void ennemyCollisionSystem();
            bool ennemyCollisionWithObject(Transform *playerTransfromComponent, Collision *playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> powerUpComponent);
            bool collisionWithPowerUp(Transform *playerTransfromComponent, Collision *playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> powerUpComponent);
            void collisionWithObstable();
            bool checkCollision(Transform *playerTransform, Collision *playerCollision,
                                Transform *objectTransform, Collision *objectCollision);

        protected:
        private:
            std::vector<std::shared_ptr<IEntities>> &_player;
            std::vector<std::shared_ptr<IEntities>> &_powerUp;
            std::vector<std::shared_ptr<IEntities>> &_objectAndEnnemy;
    };
} // namespace game_engine

#endif /* !COLLISIONSYSTEM_HPP_ */
