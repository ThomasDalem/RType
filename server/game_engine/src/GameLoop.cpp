/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

game_engine::GameLoop::GameLoop(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities)
{
    _entities = entities;
    moveSystem = MoveSystem(entities);
    deathSystem = DeathSystem(entities);
    spawnSystem = SpawnSystem(entities);
    collisionSystem = CollisionSystem(
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, entities),
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::POWERUP}, entities),
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMY, game_engine::EntitiesType::STAGEOBSTACLE, game_engine::EntitiesType::DESTROYABLETILE}, entities));
    damageSystem = DamageSystem(
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, entities),
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMY}, entities),
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::BULLET, game_engine::EntitiesType::STAGEOBSTACLE, game_engine::EntitiesType::DESTROYABLETILE}, entities));
}

game_engine::GameLoop::~GameLoop()
{
}

bool game_engine::GameLoop::areTherePlayers()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> playersList;

    if (EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities)->empty())
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