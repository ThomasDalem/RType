/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DeathSystem
*/

#include "DeathSystem.hpp"

game_engine::DeathSystem::DeathSystem(std::vector<std::shared_ptr<IEntities>> &entities) : _entities(entities)
{
}

game_engine::DeathSystem::~DeathSystem()
{
}

void game_engine::DeathSystem::deathSystem()
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEntitieIter;
    Health *entitieHealthComponent;
    std::vector<std::shared_ptr<AComponents>> entitieComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (listEntitieIter = _entities.begin(); listEntitieIter != _entities.end(); listEntitieIter++) {
        if (listEntitieIter->get()->getEntitiesID() != EntitiesType::STAGEOBSTACLE && listEntitieIter->get()->getEntitiesID() != EntitiesType::MUSIC
            && listEntitieIter->get()->getEntitiesID() != EntitiesType::ENVIRONNEMENT) {
            entitieComponent = listEntitieIter->get()->getComponentList();
            if (isDead(entitieComponent))
                listEntitieIter = _entities.erase(listEntitieIter);
        }
    }
}

bool game_engine::DeathSystem::isDead(std::vector<std::shared_ptr<AComponents>> entitieComponent)
{
    Health *entitieHealthComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (entitieComponentIter = entitieComponent.begin(); entitieComponentIter != entitieComponent.end(); ++entitieComponentIter) {
        if (entitieComponentIter->get()->getType() == ComponentType::HEALTH)
            entitieHealthComponent = static_cast<Health *>(entitieComponentIter->get());
    }
    if (entitieHealthComponent->getDamabeable() == true && entitieHealthComponent->getHealthPoint() == 0)
        return (true);
    return (false);
}