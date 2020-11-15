/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DeathSystem
*/

#include "DeathSystem.hpp"

using namespace std;

game_engine::DeathSystem::DeathSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities,
    SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &messagesToSend) :
    _entities(entities), _messagesToSend(messagesToSend)
{
}

game_engine::DeathSystem::~DeathSystem()
{
}

void game_engine::DeathSystem::incScoreForAllPlayer()
{
    std::shared_ptr<std::vector<shared_ptr<game_engine::IEntities>>> _player = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    vector<shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    Player *player;

    for (listPlayerIter = _player->begin(); listPlayerIter != _player->end(); listPlayerIter++) {
        player = static_cast<Player *>(listPlayerIter->get());
        player->incScore();
    }
}

void game_engine::DeathSystem::deathSystem()
{
    vector<shared_ptr<game_engine::IEntities>>::iterator listEntitieIter;
    Health *entitieHealthComponent;
    vector<shared_ptr<AComponents>> entitieComponent;
    vector<shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (listEntitieIter = _entities->begin(); listEntitieIter != _entities->end(); listEntitieIter++) {
        if (listEntitieIter->get()->getEntitiesID() != EntitiesType::MUSIC
            && listEntitieIter->get()->getEntitiesID() != EntitiesType::ENVIRONNEMENT) {
            entitieComponent = listEntitieIter->get()->getComponentList();
            if (isDead(entitieComponent)) {
                if (EntitiesParser::isAnEnemy(listEntitieIter->get()->getEntitiesID())) {
                    spawnPowerUp(listEntitieIter->get());
                    incScoreForAllPlayer();
                }
                if (listEntitieIter->get()->getEntitiesID() == EntitiesType::PLAYER) {
                    deadClient(listEntitieIter);
                    listEntitieIter = _entities->begin();
                } else {
                    network::UDPClientMessage suppressMessage = {network::SendEvent::REMOVE, listEntitieIter->get()->getEntitiesID(),
                        listEntitieIter->get()->getUniqueID()};
                    _messagesToBroadcast.push(suppressMessage);
                    listEntitieIter = _entities->erase(listEntitieIter);
                    listEntitieIter = _entities->begin();
                }
            }
        }
    }
}

void game_engine::DeathSystem::disconnectClient(boost::asio::ip::udp::endpoint clientEndpoint)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator playerListIter;
    game_engine::Player *player;
    network::UDPClientMessage suppressMessage;

    for (playerListIter = _entities->begin(); playerListIter != _entities->end(); playerListIter++) {
        if (playerListIter->get()->getEntitiesID() == EntitiesType::PLAYER) {
            player = static_cast<Player *>(playerListIter->get());
            if (clientEndpoint == player->getClientEndpoint()) {
                deadClient(playerListIter);
                playerListIter = _entities->begin();
                return;
            }
        }
    }
}

void game_engine::DeathSystem::deadClient(vector<shared_ptr<game_engine::IEntities>>::iterator listEntitieIter) {
    Player *player = static_cast<Player *>(listEntitieIter->get());
    network::UDPClientMessage deadMessage = {network::SendEvent::DEAD, listEntitieIter->get()->getEntitiesID(), listEntitieIter->get()->getUniqueID()};
    network::UDPClientMessage suppressMessage = {network::SendEvent::REMOVE, listEntitieIter->get()->getEntitiesID(), listEntitieIter->get()->getUniqueID()};

    std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>> message =
        std::make_unique<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>(deadMessage, player->getClientEndpoint());
    _messagesToSend.push(message);
    _messagesToBroadcast.push(suppressMessage);
    _entities->erase(listEntitieIter);
}

bool game_engine::DeathSystem::isDead(vector<shared_ptr<AComponents>> entitieComponent)
{
    Health *entitieHealthComponent;
    Transform *entitieTransformComponent;
    Collision *entitieCollisionComponent;
    vector<shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (entitieComponentIter = entitieComponent.begin(); entitieComponentIter != entitieComponent.end(); ++entitieComponentIter) {
        if (entitieComponentIter->get()->getType() == ComponentType::HEALTH)
            entitieHealthComponent = static_cast<Health *>(entitieComponentIter->get());
        if (entitieComponentIter->get()->getType() == ComponentType::TRANSFORM)
            entitieTransformComponent = static_cast<Transform *>(entitieComponentIter->get());
        if (entitieComponentIter->get()->getType() == ComponentType::COLLISION)
            entitieCollisionComponent = static_cast<Collision *>(entitieComponentIter->get());
    }
    if (entitieHealthComponent->getDamabeable() && entitieHealthComponent->getHealthPoint() == 0 ||
        checkGameBorder(*entitieTransformComponent, *entitieCollisionComponent))
        return (true);
    return (false);
}

void game_engine::DeathSystem::spawnPowerUp(game_engine::IEntities *entitie)
{
    int powerUpSpawn = rand() % 2;
    game_engine::Enemy * ennemy = static_cast<Enemy *>(entitie);

    if (powerUpSpawn == 1)
        return;
    _entities->push_back(make_shared<PowerUp>(ennemy->getTransform()->getPosition()));
}

bool game_engine::DeathSystem::checkGameBorder(Transform &transform, Collision &collision)
{
    if (transform.getPosition().y + transform.getDirection().y < 0 ||
        transform.getPosition().y + transform.getDirection().y > 1080 ||
        transform.getPosition().x + transform.getDirection().x > 1920 ||
        (transform.getPosition().x + transform.getDirection().x + collision.getRectSize().L) <= 0)
        return (true);
    return (false);
}

std::queue<network::UDPClientMessage> &game_engine::DeathSystem::getMessagesToBroadcast()
{
    return _messagesToBroadcast;
}
