/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

game_engine::GameLoop::GameLoop(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities):
    server(8081), _entities(entities), moveSystem(entities), deathSystem(entities),
    spawnSystem(entities), collisionSystem(entities), damageSystem(entities)
{
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
            if (message->second == player->getClientEndpoint()) {
                player = static_cast<Player *>(playerListIter->get());
                player->addNewInput(message->first.event, message->first.value);
                playerExisting = true;
            }
        }
        if (playerExisting == false)
            spawnSystem.newPlayer(message->first.playerID);
    }

    if (playersList->empty())
        return (false);
    return (true);
}

void game_engine::GameLoop::sendToClients()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> playersList = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator playerListIter;
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator entitiesListIter;
    std::vector<std::shared_ptr<AComponents>> entitiesComponents;
    game_engine::Player *player;
    Transform *entitieTransfromComponent;
    Collision *entitieCollisionComponent;
    Health *entitieHealthComponent;

    network::UDPClientMessage clientMessage;

    for (entitiesListIter = _entities->begin(); entitiesListIter != _entities->end(); entitiesListIter++) {
        entitiesComponents = entitiesListIter->get()->getComponentList();
        getComponentToDisp(entitiesComponents, entitieTransfromComponent, entitieCollisionComponent);
        clientMessage.entitieType = entitiesListIter->get()->getEntitiesID();
        clientMessage.uniqueID = entitiesListIter->get()->getUniqueID();
        clientMessage.pos[0] = entitieTransfromComponent->getPosition().x;
        clientMessage.pos[1] = entitieTransfromComponent->getPosition().y;
        clientMessage.rotation = entitieTransfromComponent->getRotation();
        clientMessage.spriteRectangle[0] = entitieCollisionComponent->getRectSize().x;
        clientMessage.spriteRectangle[1] = entitieCollisionComponent->getRectSize().y;
        clientMessage.spriteRectangle[2] = entitieCollisionComponent->getRectSize().L;
        clientMessage.spriteRectangle[3] = entitieCollisionComponent->getRectSize().l;
        server.broadcastDispClassMessage(clientMessage);
    }
    for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
        player = static_cast<Player *>(playerListIter->get());
        clientMessage.pos[0] = player->getHealth()->getHealthPoint();
        clientMessage.pos[1] = player->getScore();
        clientMessage.rotation = 0;
        clientMessage.spriteRectangle[0];
    }
}

void game_engine::GameLoop::getComponentToDisp(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Collision *collisionComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
    for (componentListIter = componentList.begin(); componentListIter != componentList.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
            transfromComponent = static_cast<Transform *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::COLLISION)
            collisionComponent = static_cast<Collision *>(componentListIter->get());
    }
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