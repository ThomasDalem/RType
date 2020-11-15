/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DamageSystem
*/

#include "DamageSystem.hpp"

game_engine::DamageSystem::DamageSystem()
{
}

game_engine::DamageSystem::DamageSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> list) : _entities(list)
{
}

game_engine::DamageSystem::~DamageSystem()
{
}


game_engine::DamageSystem &game_engine::DamageSystem::operator=(const game_engine::DamageSystem &damageSystem)
{
    _player = damageSystem._player;
    _ennemy = damageSystem._ennemy;
    _object = damageSystem._object;
    return (*this);
}

void game_engine::DamageSystem::damageSystem()
{
    _player = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    _ennemy = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMYALIEN,
        game_engine::EntitiesType::ENEMYBATTLESHIP, game_engine::EntitiesType::ENEMYTROOPER}, _entities);
    _object = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::BULLET, game_engine::EntitiesType::STAGEOBSTACLE, game_engine::EntitiesType::DESTROYABLETILE}, _entities);
    applyDamage();
}

void game_engine::DamageSystem::applyDamage()
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
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;

    for (playerIter = _player->begin(); playerIter != _player->end(); playerIter++) {
        playerComponent = playerIter->get()->getComponentList();
        for (componentListIter = playerComponent.begin(); componentListIter != playerComponent.end(); ++componentListIter) {
            if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::HEALTH)
                healthComponent = static_cast<Health *>(componentListIter->get());
        }
        for (objectIter = _object->begin(); objectIter != _object->end(); objectIter++) {
            objectComponent = objectIter->get()->getComponentList();
            if (checkCollisionObject(*transfromComponent, *collisionComponent, objectComponent, true))
                healthComponent->getDamage();
        }
        for (ennemyIter = _ennemy->begin(); ennemyIter != _ennemy->end(); ennemyIter++) {
            ennemyComponent = ennemyIter->get()->getComponentList();
            if (checkCollisionObject(*transfromComponent, *collisionComponent, objectComponent, true)) {
                healthComponent->getDamage();
            }
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

    if (_ennemy->size() == 0)
        return;
    for (ennemyIter = _ennemy->begin(); ennemyIter != _ennemy->end(); ennemyIter++) {
        ennemyComponent = ennemyIter->get()->getComponentList();
        std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
        for (componentListIter = ennemyComponent.begin(); componentListIter != ennemyComponent.end(); ++componentListIter) {
            if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::HEALTH)
                healthComponent = static_cast<Health *>(componentListIter->get());
        }
        for (objectIter = _object->begin(); objectIter != _object->end(); objectIter++) {
            objectComponent = objectIter->get()->getComponentList();
            if (objectIter->get()->getEntitiesID() == EntitiesType::BULLET && checkCollisionObject(*transfromComponent, *collisionComponent, objectComponent, false)) {
                healthComponent->getDamage();
            }
        }
    }
}

void game_engine::DamageSystem::environnementDamageSystem()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> obstacleList = std::make_shared<std::vector<std::shared_ptr<IEntities>>>();
    std::vector<std::shared_ptr<IEntities>>::iterator obstacleIter;
    std::vector<std::shared_ptr<AComponents>> obstacleComponents;
    Transform *transfromComponent;
    Collision *collisionComponent;
    Health *healthComponent;
    std::vector<std::shared_ptr<IEntities>>::iterator envIter;
    std::vector<std::shared_ptr<AComponents>> envComponent;

    obstacleList = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::DESTROYABLETILE, game_engine::EntitiesType::STAGEOBSTACLE}, _object);
    if (obstacleList->size() == 0)
        return;
    for (obstacleIter = obstacleList->begin(); obstacleIter != obstacleList->end(); obstacleIter++) {
        obstacleComponents = obstacleIter->get()->getComponentList();
        std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
        for (componentListIter = obstacleComponents.begin(); componentListIter != obstacleComponents.end(); ++componentListIter) {
            if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(componentListIter->get());
            if (componentListIter->get()->getType() == ComponentType::HEALTH)
                healthComponent = static_cast<Health *>(componentListIter->get());
        }
        for (envIter = _object->begin(); envIter != _object->end(); envIter++) {
            envComponent = envIter->get()->getComponentList();
            if (envIter->get()->getEntitiesID() == EntitiesType::BULLET && checkCollisionObject(*transfromComponent, *collisionComponent, envComponent, false)) {
                healthComponent->getDamage();
            }
        }
    }
}

bool game_engine::DamageSystem::checkCollisionObject(Transform &objectTransfromComponent, Collision &objectCollisionComponent,
                                                    std::vector<std::shared_ptr<AComponents>> &bulletComponent, bool canObjectDamagePlayer)
{
    std::vector<std::shared_ptr<AComponents>>::iterator bulletComponentIter;
    Transform *bulletTransfromComponent;
    Collision *bulletCollisionComponent;
    Health *bulletHealthComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;

    for (componentListIter = bulletComponent.begin(); componentListIter != bulletComponent.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM)
            bulletTransfromComponent = static_cast<Transform *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::COLLISION)
            bulletCollisionComponent = static_cast<Collision *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::HEALTH)
            bulletHealthComponent = static_cast<Health *>(componentListIter->get());
    }
    if (bulletCollisionComponent->getCanDamagePlayer() == canObjectDamagePlayer && checkCollision(objectTransfromComponent, objectCollisionComponent, *bulletTransfromComponent, *bulletCollisionComponent)) {
        bulletHealthComponent->getDamage();
        return (true);
    }
    return (false);
}

void game_engine::DamageSystem::getDamageComponent(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Collision *collisionComponent, Health *healthComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;

    for (componentListIter = componentList.begin(); componentListIter != componentList.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::TRANSFORM) {
            transfromComponent = static_cast<Transform *>(componentListIter->get());
            std::cout << transfromComponent->getPosition().x << " " << transfromComponent->getPosition().y << std::endl;
        }
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
