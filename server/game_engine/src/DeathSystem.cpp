/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DeathSystem
*/

#include "DeathSystem.hpp"

using namespace std;
game_engine::DeathSystem::DeathSystem()
{
}

game_engine::DeathSystem::DeathSystem(shared_ptr<vector<shared_ptr<IEntities>>> entities) : _entities(entities)
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
    vector<shared_ptr<game_engine::IEntities>>::iterator listEntitieIter;
    Health *entitieHealthComponent;
    vector<shared_ptr<AComponents>> entitieComponent;
    vector<shared_ptr<AComponents>>::iterator entitieComponentIter;

    for (listEntitieIter = _entities->begin(); listEntitieIter != _entities->end(); listEntitieIter++) {
        if (listEntitieIter->get()->getEntitiesID() != EntitiesType::MUSIC
            && listEntitieIter->get()->getEntitiesID() != EntitiesType::ENVIRONNEMENT) {
            entitieComponent = listEntitieIter->get()->getComponentList();
            if (isDead(entitieComponent)) {
                if (EntitiesParser::isAnEnemy(listEntitieIter->get()->getEntitiesID()))
                    spawnPowerUp(listEntitieIter->get());
                if (listEntitieIter->get()->getEntitiesID() == EntitiesType::PLAYER) {
                    deadClient(listEntitieIter, server);
                    listEntitieIter = _entities->begin();
                } else {
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

void game_engine::DeathSystem::deadClient(vector<shared_ptr<game_engine::IEntities>>::iterator listEntitieIter, network::NetUDPServer &server) {
    Player *player = static_cast<Player *>(listEntitieIter->get());
    network::UDPClientMessage deadMessage = {network::SendEvent::DEAD, listEntitieIter->get()->getEntitiesID(), listEntitieIter->get()->getUniqueID()};
    network::UDPClientMessage suppressMessage = {network::SendEvent::REMOVE, listEntitieIter->get()->getEntitiesID(), listEntitieIter->get()->getUniqueID()};

    server.sendMessage(deadMessage, player->getClientEndpoint());
    server.broadcastMessage(suppressMessage);
    _entities->erase(listEntitieIter);
}

void game_engine::DeathSystem::disconnectClient(vector<shared_ptr<game_engine::IEntities>>::iterator listEntitieIter, network::NetUDPServer &server)
{
    Player *player = static_cast<Player *>(listEntitieIter->get());
    network::UDPClientMessage suppressMessage = {network::SendEvent::DESCONNECTCLIENT, listEntitieIter->get()->getEntitiesID(),
        listEntitieIter->get()->getUniqueID()};

    server.sendMessage(suppressMessage, player->getClientEndpoint());
    server.killClient(player->getClientEndpoint());
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