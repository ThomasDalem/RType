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
#include "EntitiesParser.hpp"


namespace game_engine
{
    class DamageSystem
    {
    public:
        DamageSystem();
        DamageSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> list);
        ~DamageSystem();
        DamageSystem &operator=(const DamageSystem &moveSystem);
        void applyDamage();
        void damageSystem();
        void ennemyDamageSystem();
        void environnementDamageSystem();
        void getDamageComponent(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Collision *collisionComponent, Health *healthComponent);
        bool checkCollisionWithObject(Transform &transfromComponent, Collision &collisionComponent, std::vector<std::shared_ptr<AComponents>> &objectComponent);
        bool checkCollisionObject(Transform &playerTransfromComponent, Collision &playerCollisionComponent,
            std::vector<std::shared_ptr<AComponents>> &bulletComponent, bool canObjectDamagePlaye);
        bool isCollision();
        bool checkCollision(Transform &playerTransfrom, Collision & playerCollision, Transform &objectTransform, Collision &objectCollision);

    protected:
    private:
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _player;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _ennemy;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _object;
    };
} // namespace game_engine
#endif /* !DAMAGESYSTEM_HPP_ */
