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
        void moveSystem(std::map<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>> map);

    protected:
    private:
    };
} // namespace game_engine
#endif /* !DAMAGESYSTEM_HPP_ */
