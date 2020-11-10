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
    int newPlayerID = 0;

    while (server.hasMessages()) {
        playerExisting = false;
        message = server.getFirstMessage();
        if (message->first.playerID == -1) {
            for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
                if (message->second == player->getClientEndpoint()) {
                    player = static_cast<Player *>(playerListIter->get());
                    player->addNewInput(message->first.event, message->first.value);
                    playerExisting = true;
                }
            }
        }
        else {
            newPlayerID = spawnSystem.newPlayer();
        }
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
    Render *entitieRenderComponent;
    Health *entitieHealthComponent;

    network::UDPClientMessage clientMessage;

    for (entitiesListIter = _entities->begin(); entitiesListIter != _entities->end(); entitiesListIter++) {
        entitiesComponents = entitiesListIter->get()->getComponentList();
        getComponentToDisp(entitiesComponents, entitieTransfromComponent, entitieRenderComponent);
        clientMessage.entitieType = entitiesListIter->get()->getEntitiesID();
        clientMessage.uniqueID = entitiesListIter->get()->getUniqueID();
        clientMessage.value[0] = 1;
        clientMessage.value[1] = entitieTransfromComponent->getPosition().x;
        clientMessage.value[2] = entitieTransfromComponent->getPosition().y;
        clientMessage.value[3] = entitieTransfromComponent->getRotation();
        clientMessage.value[4] = entitieRenderComponent->getRect().x;
        clientMessage.value[5] = entitieRenderComponent->getRect().y;
        clientMessage.value[6] = entitieRenderComponent->getRect().L;
        clientMessage.value[7] = entitieRenderComponent->getRect().l;
        server.broadcastDispClassMessage(clientMessage);
    }
    for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
        player = static_cast<Player *>(playerListIter->get());
        if (player->getHealth()->getHealthPoint() > 0) {
            clientMessage.entitieType = EntitiesType::ENVIRONNEMENT;
            clientMessage.value[0] = 1;
            clientMessage.value[1] = player->getHealth()->getHealthPoint();
            clientMessage.value[2] = player->getScore();
            clientMessage.value[3] = 0;
        }
        else {
            clientMessage.value[0] = 0;
        }
        server.sendDispClassMessage(clientMessage, player->getClientEndpoint()); 
    }
}

void game_engine::GameLoop::getComponentToDisp(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Render *renderComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;

    for (componentListIter = componentList.begin(); componentListIter != componentList.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
            transfromComponent = static_cast<Transform *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::RENDER)
            renderComponent = static_cast<Render *>(componentListIter->get());
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