/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

game_engine::GameLoop::GameLoop(std::vector<std::shared_ptr<IEntities>> &entities): _entities(entities)
{
}

game_engine::GameLoop::~GameLoop()
{
}

bool game_engine::GameLoop::areTherePlayers()
{
    std::vector<std::shared_ptr<game_engine::IEntities>> playersList;

    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities, playersList);
    if (playersList.empty())
        return (false);
    //get message, parse
    //send message
    return (true);
}

void game_engine::GameLoop::gameLoop()
{
    while (areTherePlayers() == false);
    //un joueur c'est connecté
    while (areTherePlayers()) {
        moveSystem.moveSystem();
        collisionSystem.collisionSystem();
        damageSystem.damageSystem();
        deathSystem.deathSystem();
        spawnSystem.spawnSystem();
    }
}