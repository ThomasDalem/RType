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
            CollisionSystem();
            CollisionSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> player, std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> powerUp, std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> objectAndEnemy);
            ~CollisionSystem();
            CollisionSystem &operator=(const CollisionSystem &moveSystem);
            void collisionSystem();
            void ennemyCollisionSystem();
            bool ennemyCollisionWithObject(Transform &playerTransfromComponent, Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> powerUpComponent);
            bool collisionWithPowerUp(Transform &playerTransfromComponent, Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> powerUpComponent);
            void collisionWithObstable();
            bool checkCollision(Transform &playerTransform, Collision &playerCollision,
                                Transform &objectTransform, Collision &objectCollision);

        protected:
        private:
            std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _player;
            std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _powerUp;
            std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _objectAndEnemy;
    };
} // namespace game_engine

#endif /* !COLLISIONSYSTEM_HPP_ */
