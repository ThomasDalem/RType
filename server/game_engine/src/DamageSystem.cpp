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
        getDamageComponent(playerComponent, transfromComponent, collisionComponent, healthComponent);
        for (objectIter = _object.begin(); objectIter != _object.end(); objectIter++) {
            objectComponent = objectIter->get()->getComponentList();
            if (checkCollisionWithObject(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
        for (ennemyIter = _ennemy.begin(); ennemyIter != _ennemy.end(); ennemyIter++) {
            ennemyComponent = ennemyIter->get()->getComponentList();
            if (checkCollisionWithObject(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
    }
    ennemyDamageSystem();
    environnementDamageSystem();
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

    for (ennemyIter = _ennemy.begin(); ennemyIter != _ennemy.end(); ennemyIter++) {
        ennemyComponent = ennemyIter->get()->getComponentList();
        getDamageComponent(ennemyComponent, transfromComponent, collisionComponent, healthComponent);
        for (objectIter = _object.begin(); objectIter != _object.end(); objectIter++) {
            objectComponent = objectIter->get()->getComponentList();
            if (objectIter->get()->getEntitiesID() == EntitiesType::BULLET && checkCollisionWithAllieBullet(*transfromComponent, *collisionComponent, objectComponent) == true)
                healthComponent->getDamage();
        }
    }
}

void game_engine::DamageSystem::environnementDamageSystem()
{
    std::vector<std::shared_ptr<game_engine::IEntities>> bulletList;
    std::vector<std::shared_ptr<IEntities>>::iterator bulletIter;
    std::vector<std::shared_ptr<AComponents>> bulletComponents;
    Transform *transfromComponent;
    Collision *collisionComponent;
    Health *healthComponent;
    std::vector<std::shared_ptr<IEntities>>::iterator envIter;
    std::vector<std::shared_ptr<AComponents>> envComponent;

    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::BULLET}, _object, bulletList);
    for (bulletIter = bulletList.begin(); bulletIter != bulletList.end(); bulletIter++) {
        bulletComponents = bulletIter->get()->getComponentList();
        getDamageComponent(bulletComponents, transfromComponent, collisionComponent, healthComponent);
        for (envIter = _object.begin(); envIter != _object.end(); envIter++) {
            envComponent = envIter->get()->getComponentList();
            if (envIter->get()->getEntitiesID() != EntitiesType::BULLET && checkCollisionWithObject(*transfromComponent, *collisionComponent, envComponent) == true)
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

    getDamageComponent(objectComponent, objectTransfromComponent, objectCollisionComponent, objectHealthComponent);
    if (objectCollisionComponent->getCanDamagePlayer() == true && checkCollisionWithAllieBullet(playerTransfromComponent, playerCollisionComponent, *objectTransfromComponent, *objectCollisionComponent)) {
        objectHealthComponent->getDamage();
        return (true);
    }
    return (false);
}


bool game_engine::DamageSystem::checkCollisionWithAllieBullet(Transform &playerTransfromComponent,
                                                         Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> bulletComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator bulletComponentIter;
    Transform *bulletTransfromComponent;
    Collision *bulletCollisionComponent;
    Health *bulletHealthComponent;

    getDamageComponent(bulletComponent, bulletTransfromComponent, bulletCollisionComponent, bulletHealthComponent);
    if (bulletCollisionComponent->getCanDamagePlayer() == false && checkCollision(playerTransfromComponent, playerCollisionComponent, *bulletTransfromComponent, *bulletCollisionComponent)) {
        bulletHealthComponent->getDamage();
        return (true);
    }
    return (false);
}

void game_engine::DamageSystem::getDamageComponent(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Collision *collisionComponent, Health *healthComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
    for (componentListIter = componentList.begin(); componentListIter != componentList.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
            transfromComponent = static_cast<Transform *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::COLLISION)
            collisionComponent = static_cast<Collision *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::HEALTH)
            healthComponent = static_cast<Health *>(componentListIter->get());
    }
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
