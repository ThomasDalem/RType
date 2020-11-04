/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DamageSystem
*/

#ifndef DAMAGESYSTEM_HPP_
#define DAMAGESYSTEM_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include "Components/Collision.hpp"
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "EntitiesEnum.hpp"
#include "Entities/IEntities.hpp"


namespace game_engine
{
    class DamageSystem
    {
    public:
        DamageSystem(std::vector<std::shared_ptr<IEntities>> &player, std::vector<std::shared_ptr<IEntities>> &ennemy, std::vector<std::shared_ptr<IEntities>> &object);
        ~DamageSystem();

        void damageSystem();
        void ennemyDamageSystem();
        bool checkCollisionWithObject(Transform &transfromComponent, Collision &collisionComponent, std::vector<std::shared_ptr<AComponents>> objectComponent);
        bool checkCollisionWithEnemy(Transform &transfromComponent, Collision &collisionComponent, std::vector<std::shared_ptr<AComponents>> ennemyComponent);
        bool isCollision();
        bool checkCollision(Transform &playerTransfrom, Collision & playerCollision, Transform &objectTransform, Collision &objectCollision);

    protected:
    private:
        std::vector<std::shared_ptr<IEntities>> &_player;
        std::vector<std::shared_ptr<IEntities>> &_ennemy;
        std::vector<std::shared_ptr<IEntities>> &_object;
    };
} // namespace game_engine
#endif /* !DAMAGESYSTEM_HPP_ */
