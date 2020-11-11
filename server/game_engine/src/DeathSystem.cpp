/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DeathSystem
*/

#include "DeathSystem.hpp"

game_engine::DeathSystem::DeathSystem()
{
}

game_engine::DeathSystem::DeathSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities) : _entities(entities)
{
}

game_engine::DeathSystem::~DeathSystem()
{
}

game_engine::DeathSystem &game_engine::DeathSystem::operator=(const game_engine::DeathSystem &deathSystem)
{
    _entities = deathSystem._entities;
    return (*this);
}

void game_engine::DeathSystem::deathSystem(network::NetUDPServer &server)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEntitieIter;
    Health *entitieHealthComponent;
    std::vector<std::shared_ptr<AComponents>> entitieComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (listEntitieIter = _entities->begin(); listEntitieIter != _entities->end(); listEntitieIter++) {
        if (listEntitieIter->get()->getEntitiesID() != EntitiesType::MUSIC
            && listEntitieIter->get()->getEntitiesID() != EntitiesType::ENVIRONNEMENT) {
            entitieComponent = listEntitieIter->get()->getComponentList();
            if (isDead(entitieComponent)) {
                if (EntitiesParser::isAnEnemy(listEntitieIter->get()->getEntitiesID()))
                    spawnPowerUp(listEntitieIter->get());
                if (listEntitieIter->get()->getEntitiesID() == EntitiesType::PLAYER) {
                    // disconnectClient(listEntitieIter, server);
                    deadClient(listEntitieIter, server);
                    listEntitieIter = _entities->begin();
                }
                else {
                    network::UDPClientMessage suppressMessage = {network::SendEvent::REMOVE, listEntitieIter->get()->getEntitiesID(),
                        listEntitieIter->get()->getUniqueID()};
                    server.broadcastMessage(suppressMessage);
                    listEntitieIter = _entities->erase(listEntitieIter);
                    listEntitieIter = _entities->begin();
                }
            }
        }
    }
}

void game_engine::DeathSystem::deadClient(std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEntitieIter, network::NetUDPServer &server) {
    Player *player = static_cast<Player *>(listEntitieIter->get());
    network::UDPClientMessage suppressMessage = {network::SendEvent::DEAD, listEntitieIter->get()->getEntitiesID(),
        listEntitieIter->get()->getUniqueID()};

    server.sendMessage(suppressMessage, player->getClientEndpoint());
}

void game_engine::DeathSystem::disconnectClient(std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEntitieIter, network::NetUDPServer &server)
{
    Player *player = static_cast<Player *>(listEntitieIter->get());
    network::UDPClientMessage suppressMessage = {network::SendEvent::DESCONNECTCLIENT, listEntitieIter->get()->getEntitiesID(),
        listEntitieIter->get()->getUniqueID()};

    server.sendMessage(suppressMessage, player->getClientEndpoint());
    server.killClient(player->getClientEndpoint());
    _entities->erase(listEntitieIter);
}

bool game_engine::DeathSystem::isDead(std::vector<std::shared_ptr<AComponents>> entitieComponent)
{
    Health *entitieHealthComponent;
    Transform *entitieTransformComponent;
    Collision *entitieCollisionComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (entitieComponentIter = entitieComponent.begin(); entitieComponentIter != entitieComponent.end(); ++entitieComponentIter) {
        if (entitieComponentIter->get()->getType() == ComponentType::HEALTH)
            entitieHealthComponent = static_cast<Health *>(entitieComponentIter->get());
        if (entitieComponentIter->get()->getType() == ComponentType::TRANSFORM)
            entitieTransformComponent = static_cast<Transform *>(entitieComponentIter->get());
        if (entitieComponentIter->get()->getType() == ComponentType::COLLISION)
            entitieCollisionComponent = static_cast<Collision *>(entitieComponentIter->get());
    }
    if (entitieHealthComponent->getDamabeable() == true && entitieHealthComponent->getHealthPoint() == 0 ||
        checkGameBorder(*entitieTransformComponent, *entitieCollisionComponent) == true)
        return (true);
    return (false);
}

void game_engine::DeathSystem::spawnPowerUp(game_engine::IEntities *entitie)
{
    int powerUpSpawn = rand() % 2;
    game_engine::Enemy * ennemy = static_cast<Enemy *>(entitie);

    if (powerUpSpawn == 1)
        return;
    _entities->push_back(std::make_shared<PowerUp>(ennemy->getTransform()->getPosition()));
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