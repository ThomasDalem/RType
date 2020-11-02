/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DamageSystem
*/

#include "DamageSystem.hpp"

game_engine::DamageSystem::DamageSystem()
{
}

game_engine::DamageSystem::~DamageSystem()
{
}

void game_engine::DamageSystem::damageSystem(std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>> entitie,
    std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>> bullet)
{
    std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>>::iterator iter;

    for (iter = entitie.begin(); iter != entitie.end(); ++iter) {
        std::map<int, std::tuple<EntitiesType, std::shared_ptr<Health>, std::shared_ptr<Collision>, std::shared_ptr<Transform>>>::iterator bulletIter;
        for (bulletIter = bullet.begin(); iter != bullet.end(); bulletIter++) {
            if (isCollision(std::get<2>(iter->second), std::get<3>(iter->second), std::get<2>(bulletIter->second), std::get<3>(bulletIter->second)))
                std::get<1>(iter->second)->healthPoint--;
        }
    }
}

bool game_engine::DamageSystem::isCollision(std::shared_ptr<Collision> entitieCollision, std::shared_ptr<Transform> entitieTransform,
    std::shared_ptr<Collision> bulletCollision, std::shared_ptr<Transform> bulletTransform)
{
    if (bulletTransform->position.x > entitieTransform->position.x - (entitieCollision->rectSize.L / 2) &&
        bulletTransform->position.x < entitieTransform->position.x + (entitieCollision->rectSize.L / 2) &&
        bulletTransform->position.y > entitieTransform->position.y - (entitieCollision->rectSize.l / 2) &&
        bulletTransform->position.y < entitieTransform->position.y + (entitieCollision->rectSize.l / 2))
        return (true);
    return (false);
}