/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DamageSystem
*/

#include "DamageSystem.hpp"

game_engine::DamageSystem::DamageSystem(std::vector<std::shared_ptr<IEntities>> &player,
                                        std::vector<std::shared_ptr<IEntities>> &ennemy, std::vector<std::shared_ptr<IEntities>> &object) : _player(player), _ennemy(ennemy), _object(object)
{
}

game_engine::DamageSystem::~DamageSystem()
{
}

void game_engine::DamageSystem::damageSystem()
{
    std::vector<std::shared_ptr<IEntities>>::iterator playerIter;
    std::vector<std::shared_ptr<AComponents>> playerComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator playerComponentIter;
    Transform *transfromComponent;
    Collision *collisionComponent;
    Health *healthComponent;
    std::vector<std::shared_ptr<IEntities>>::iterator ennemyIter;
    std::vector<std::shared_ptr<AComponents>> ennemyComponent;
    std::vector<std::shared_ptr<IEntities>>::iterator objectIter;
    std::vector<std::shared_ptr<AComponents>> objectComponent;

    for (playerIter = _player.begin(); playerIter != _player.end(); playerIter++)
    {
        playerComponent = playerIter->get()->getComponentList();
        for (playerComponentIter = playerComponent.begin(); playerComponentIter != playerComponent.end(); playerComponentIter++)
        {
            if (playerComponentIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(playerComponentIter->get());
            if (playerComponentIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(playerComponentIter->get());
            if (playerComponentIter->get()->getType() == ComponentType::HEALTH)
                healthComponent = static_cast<Health *>(playerComponentIter->get());
        }
        for (objectIter = _object.begin(); objectIter != _object.end(); objectIter++)
        {
            objectComponent = objectIter->get()->getComponentList();
            if (checkCollisionWithObject(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
        for (ennemyIter = _ennemy.begin(); ennemyIter != _ennemy.end(); ennemyIter++) {
            ennemyComponent = ennemyIter->get()->getComponentList();
            if (checkCollisionWithEnemy(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
    }
    ennemyDamageSystem();
}

void game_engine::DamageSystem::ennemyDamageSystem()
{
    std::vector<std::shared_ptr<IEntities>>::iterator ennemyIter;
    std::vector<std::shared_ptr<AComponents>> ennemyComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator ennemyComponentIter;
    Transform *transfromComponent;
    Collision *collisionComponent;
    Health *healthComponent;
    std::vector<std::shared_ptr<IEntities>>::iterator objectIter;
    std::vector<std::shared_ptr<AComponents>> objectComponent;

    for (ennemyIter = _ennemy.begin(); ennemyIter != _ennemy.end(); ennemyIter++)
    {
        ennemyComponent = ennemyIter->get()->getComponentList();
        for (ennemyComponentIter = ennemyComponent.begin(); ennemyComponentIter != ennemyComponent.end(); ennemyComponentIter++)
        {
            if (ennemyComponentIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(ennemyComponentIter->get());
            if (ennemyComponentIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(ennemyComponentIter->get());
            if (ennemyComponentIter->get()->getType() == ComponentType::HEALTH)
                healthComponent = static_cast<Health *>(ennemyComponentIter->get());
        }
        for (objectIter = _object.begin(); objectIter != _object.end(); objectIter++)
        {
            objectComponent = objectIter->get()->getComponentList();
            if (checkCollisionWithObject(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
    }
}

bool game_engine::DamageSystem::checkCollisionWithObject(Transform &playerTransfromComponent,
                                                         Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> objectComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator objectComponentIter;
    Transform *objectTransfromComponent;
    Collision *objectCollisionComponent;
    Health *objectHealthComponent;

    for (objectComponentIter = objectComponent.begin(); objectComponentIter != objectComponent.end(); ++objectComponentIter) {
        if (objectComponentIter->get()->getType() == ComponentType::TRANSFORM)
            objectTransfromComponent = static_cast<Transform *>(objectComponentIter->get());
        if (objectComponentIter->get()->getType() == ComponentType::COLLISION)
            objectCollisionComponent = static_cast<Collision *>(objectComponentIter->get());
        if (objectComponentIter->get()->getType() == ComponentType::HEALTH)
            objectHealthComponent = static_cast<Health *>(objectComponentIter->get());
    }
    if (checkCollision(playerTransfromComponent, playerCollisionComponent, *objectTransfromComponent, *objectCollisionComponent) && objectCollisionComponent->getCanDamagePlayer() == true) {
        objectHealthComponent->getDamage();
        return (true);
    }
    return (false);
}

bool game_engine::DamageSystem::checkCollisionWithEnemy(Transform &playerTransfromComponent,
                                                         Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> ennemyComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator ennemyComponentIter;
    Transform *objectTransfromComponent;
    Collision *objectCollisionComponent;
    Health *objectHealthComponent;

    for (ennemyComponentIter = ennemyComponent.begin(); ennemyComponentIter != ennemyComponent.end(); ++ennemyComponentIter) {
        if (ennemyComponentIter->get()->getType() == ComponentType::TRANSFORM)
            objectTransfromComponent = static_cast<Transform *>(ennemyComponentIter->get());
        if (ennemyComponentIter->get()->getType() == ComponentType::COLLISION)
            objectCollisionComponent = static_cast<Collision *>(ennemyComponentIter->get());
        if (ennemyComponentIter->get()->getType() == ComponentType::HEALTH)
            objectHealthComponent = static_cast<Health *>(ennemyComponentIter->get());
    }
    if (checkCollision(playerTransfromComponent, playerCollisionComponent, *objectTransfromComponent, *objectCollisionComponent) && objectCollisionComponent->getCanDamagePlayer() == true) {
        objectHealthComponent->getDamage();
        return (true);
    }
    return (false);
}


bool game_engine::DamageSystem::checkCollision(Transform &playerTransform, Collision &playerCollision,
                                               Transform &objectTransform, Collision &objectCollision)
{
    Vector end_pos_rect1 = Vector((playerTransform.getPosition().x + playerCollision.getRectSize().L), (playerTransform.getPosition().y + playerCollision.getRectSize().l));
    Vector end_pos_rect2 = Vector((objectTransform.getPosition().x + objectCollision.getRectSize().L), (objectTransform.getPosition().y + objectCollision.getRectSize().l));

    if (playerTransform.getPosition().x >= objectTransform.getPosition().x && playerTransform.getPosition().x <= end_pos_rect2.x &&
        playerTransform.getPosition().y >= objectTransform.getPosition().y && playerTransform.getPosition().y <= end_pos_rect2.y)
        return (true);
    if (playerTransform.getPosition().x >= objectTransform.getPosition().x && playerTransform.getPosition().x <= end_pos_rect2.x &&
        end_pos_rect1.y >= objectTransform.getPosition().y && end_pos_rect1.y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect1.x >= objectTransform.getPosition().x && end_pos_rect1.x <= end_pos_rect2.x &&
        playerTransform.getPosition().y >= objectTransform.getPosition().y && playerTransform.getPosition().y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect1.x >= objectTransform.getPosition().x && end_pos_rect1.x <= end_pos_rect2.x &&
        end_pos_rect1.y >= objectTransform.getPosition().y && end_pos_rect1.y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect2.x >= playerTransform.getPosition().x && end_pos_rect2.x <= end_pos_rect1.x &&
        end_pos_rect2.y >= playerTransform.getPosition().y && end_pos_rect2.y <= end_pos_rect1.y)
        return (true);
    return (false);
}
