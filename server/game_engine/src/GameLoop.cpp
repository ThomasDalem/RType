/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

game_engine::GameLoop::GameLoop(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities): server(8081)
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
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> playersList = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator playerListIter;
    game_engine::Player *player;
    std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> message;
    bool playerExisting = false;

    while (server.hasMessages()) {
        playerExisting = false;
        message = server.getFirstMessage();
        for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
            player = static_cast<Player *>(playerListIter->get());
            player->addNewInput(message->first.event, message->first.value);
            playerExisting = true;
        }
        if (playerExisting == false)
            spawnSystem.newPlayer(message->first.playerID);
    }

    if (playersList->empty())
        return (false);
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