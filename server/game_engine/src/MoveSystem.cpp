/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"

game_engine::MoveSystem::MoveSystem()
{
}

game_engine::MoveSystem::~MoveSystem()
{
}

void game_engine::MoveSystem::moveSystem(std::map<int, std::shared_ptr<Transform>> map)
{
    std::map<int, std::shared_ptr<Transform>>::iterator iter;

    for (iter = map.begin(); iter != map.end(); ++iter) {
        iter->second->oldPosition = iter->second->position;
        iter->second->position.x += iter->second->direction.x;
        iter->second->position.y += iter->second->direction.y;
    }
}