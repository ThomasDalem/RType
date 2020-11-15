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

void game_engine::GameLoop::respondToConnection(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator playerListIter;
    network::UDPClientMessage responseMessage;
    game_engine::Player *player;
    int newPlayerID = 0;

    memset(&responseMessage, 0, sizeof(network::UDPClientMessage));
    newPlayerID = spawnSystem.newPlayer(message->second);
    responseMessage.event = network::SendEvent::UPDATE;
    responseMessage.entitieType = 0;
    responseMessage.uniqueID = newPlayerID;

    for (playerListIter = _entities->begin(); playerListIter != _entities->end(); playerListIter++) {
        player = static_cast<Player *>(playerListIter->get());
        if (newPlayerID == player->getUniqueID())
            break;
    }
    responseMessage.value[0] = -1;
    responseMessage.value[1] = 0;
    responseMessage.value[2] = 0;
    responseMessage.value[3] = 0;
    responseMessage.value[4] = player->getRender()->getRect().x;
    responseMessage.value[5] = player->getRender()->getRect().y;
    responseMessage.value[6] = player->getRender()->getRect().L;
    responseMessage.value[7] = player->getRender()->getRect().l;
    server.sendMessage(responseMessage, message->second);
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
        if (message->first.playerID == -1 && message->first.event != network::Event::CONFIRMCONNECTION) {
            std::cout << "create new player" << std::endl;
            respondToConnection(message);
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
        if (message->first.event == network::Event::DISCONNECTION) {
            deathSystem.disconnectClient(message->second, server);
            playersList = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
            break;
        }
    }
    if (playersList->empty())
        return (false);
    return (true);
}

void game_engine::GameLoop::sendEntitiesToClient(std::vector<std::shared_ptr<game_engine::IEntities>>::iterator entitiesListIter, 
    Transform *transfrom, Render *render)
{
    network::UDPClientMessage clientMessage;

    memset(&clientMessage, 0, sizeof(network::UDPClientMessage));
    clientMessage.event = network::SendEvent::UPDATE;
    clientMessage.entitieType = entitiesListIter->get()->getEntitiesID();
    clientMessage.uniqueID = entitiesListIter->get()->getUniqueID();
    clientMessage.value[0] = 1;
    clientMessage.value[1] = transfrom->getPosition().x;
    clientMessage.value[2] = transfrom->getPosition().y;
    clientMessage.value[3] = 0;
    clientMessage.value[4] = render->getRect().x;
    clientMessage.value[5] = render->getRect().y;
    clientMessage.value[6] = render->getRect().L;
    clientMessage.value[7] = render->getRect().l;
    server.broadcastMessage(clientMessage);
}

void game_engine::GameLoop::sendHUDToClient()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> playersList = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator playerListIter;
    game_engine::Player *player;

    for (playerListIter = playersList->begin(); playerListIter != playersList->end(); playerListIter++) {
        player = static_cast<Player *>(playerListIter->get());
        network::UDPClientMessage clientMessage;
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
        server.sendMessage(clientMessage, player->getClientEndpoint());
    }
}

void game_engine::GameLoop::sendToClients()
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator entitiesListIter;
    std::vector<std::shared_ptr<AComponents>> entitiesComponents;
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
    Transform *entitieTransfromComponent;
    Render *entitieRenderComponent;

    for (entitiesListIter = _entities->begin(); entitiesListIter != _entities->end(); entitiesListIter++) {
        entitiesComponents = entitiesListIter->get()->getComponentList();
        for (componentListIter = entitiesComponents.begin(); componentListIter != entitiesComponents.end(); ++componentListIter) {
            if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
                entitieTransfromComponent = static_cast<Transform *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::RENDER)
                entitieRenderComponent = static_cast<Render *>(componentListIter->get());
        }
        sendEntitiesToClient(entitiesListIter, entitieTransfromComponent, entitieRenderComponent);
    }
    sendHUDToClient();
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

void game_engine::GameLoop::oneLoop() {
    moveSystem.moveSystem();
    collisionSystem.collisionSystem();
    damageSystem.damageSystem();
    deathSystem.deathSystem(server);
    spawnSystem.spawnSystem();
    sendToClients();
}

using namespace std;
void game_engine::GameLoop::gameLoop() {
    auto start = chrono::steady_clock::now();

    while (!areTherePlayers());
    while (areTherePlayers()) {
        auto now = chrono::steady_clock::now();
        auto diff = now - start;
        auto end = now + chrono::milliseconds(16);
        if (diff >= chrono::milliseconds(10))
            oneLoop();
        this_thread::sleep_until(end);
    }
}
