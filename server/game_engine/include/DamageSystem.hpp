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
#include<tuple>
#include "Components/Collision.hpp"
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "EntitiesEnum.hpp"

namespace game_engine
{
    class DamageSystem
    {
    public:
        DamageSystem();
        ~DamageSystem();
        void damageSystem(std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>> entitie,
                        std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>> bullet);
        bool isCollision(std::shared_ptr<Collision> entitieCollision, std::shared_ptr<Transform> entitieTransform,
                        std::shared_ptr<Collision> bulletCollision, std::shared_ptr<Transform> bulletTransform);

    protected:
    private:
    };
} // namespace game_engine
#endif /* !DAMAGESYSTEM_HPP_ */
