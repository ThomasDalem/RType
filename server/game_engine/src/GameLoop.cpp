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
        if (message->first.playerID == -1 && message->first.event != network::Event::CONFIRMCONNECTION){
            std::cout << "create new player" << std::endl;
            newPlayerID = spawnSystem.newPlayer(message->second);
            network::UDPClientMessage responseMessage = {network::SendEvent::UPDATE , 0, newPlayerID};
            memset(&responseMessage, 0, sizeof(network::UDPClientMessage));
            responseMessage.event = network::SendEvent::UPDATE;
            responseMessage.value[0] = -1;
            server.sendMessage(responseMessage, message->second);
        }
        else if (message->first.event != network::Event::CONFIRMCONNECTION) {
            for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
                player = static_cast<Player *>(playerListIter->get());
                if (message->second == player->getClientEndpoint()) {
                    player->addNewInput(message->first.event, message->first.value);
                    playerExisting = true;
                }
            }
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
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
    game_engine::Player *player;
    Transform *entitieTransfromComponent;
    Collision *entitieCollisionComponent;
    Render *entitieRenderComponent;
    Health *entitieHealthComponent;

    for (entitiesListIter = _entities->begin(); entitiesListIter != _entities->end(); entitiesListIter++) {
        network::UDPClientMessage clientMessage;
        entitiesComponents = entitiesListIter->get()->getComponentList();
        for (componentListIter = entitiesComponents.begin(); componentListIter != entitiesComponents.end(); ++componentListIter) {
            if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
                entitieTransfromComponent = static_cast<Transform *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::RENDER)
                entitieRenderComponent = static_cast<Render *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::COLLISION)
                entitieCollisionComponent = static_cast<Collision *>(componentListIter->get());
        }
        if (entitieTransfromComponent->getPosition().x != entitieTransfromComponent->getOldPosition().x ||
            entitieTransfromComponent->getPosition().y != entitieTransfromComponent->getOldPosition().y) {
            memset(&clientMessage, 0, sizeof(network::UDPClientMessage));
            clientMessage.event = network::SendEvent::UPDATE;
            clientMessage.entitieType = entitiesListIter->get()->getEntitiesID();
            clientMessage.uniqueID = entitiesListIter->get()->getUniqueID();
            clientMessage.value[0] = 1;
            clientMessage.value[1] = entitieTransfromComponent->getPosition().x;
            clientMessage.value[2] = entitieTransfromComponent->getPosition().y;
            clientMessage.value[3] = 0;
            clientMessage.value[4] = entitieRenderComponent->getRect().x;
            clientMessage.value[5] = entitieRenderComponent->getRect().y;
            clientMessage.value[6] = entitieRenderComponent->getRect().L;
            clientMessage.value[7] = entitieRenderComponent->getRect().l;
            server.broadcastMessage(clientMessage);
        }
    }
    // for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
    //     player = static_cast<Player *>(playerListIter->get());
    //     network::UDPClientMessage clientMessage;
    //     if (player->getHealth()->getHealthPoint() > 0) {
    //         clientMessage.entitieType = EntitiesType::ENVIRONNEMENT;
    //         clientMessage.value[0] = 1;
    //         clientMessage.value[1] = player->getHealth()->getHealthPoint();
    //         clientMessage.value[2] = player->getScore();
    //         clientMessage.value[3] = 0;
    //     }
    //     else {
    //         clientMessage.value[0] = 0;
    //     }
    //     server.sendMessage(clientMessage, player->getClientEndpoint());
    // }
}

void game_engine::GameLoop::getComponentToDisp(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Render *renderComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;

    for (componentListIter = componentList.begin(); componentListIter != componentList.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM) {
            std::cout << "get transform" << std::endl;
            transfromComponent = static_cast<Transform *>(componentListIter->get());
        }
        if (componentListIter->get()->getType() == ComponentType::RENDER)
            renderComponent = static_cast<Render *>(componentListIter->get());
    }
}

void game_engine::GameLoop::gameLoop()
{
    auto start = std::chrono::steady_clock::now();

    while (!areTherePlayers());
    //un joueur c'est connecté
    while (areTherePlayers()) {
        auto now = std::chrono::steady_clock::now();
        auto diff = now - start;
        auto end = now + std::chrono::milliseconds(16);
        if (diff >= std::chrono::milliseconds(10)) {
            moveSystem.moveSystem();
            collisionSystem.collisionSystem();
            damageSystem.damageSystem();
            deathSystem.deathSystem(server);
            spawnSystem.spawnSystem();
            sendToClients();
        }
        std::this_thread::sleep_until(end);
    }
}
