/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

game_engine::CollisionSystem::CollisionSystem()
{
}

game_engine::CollisionSystem::CollisionSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> list)
    : _entities(list)
{
}

game_engine::CollisionSystem::~CollisionSystem()
{
}

game_engine::CollisionSystem &game_engine::CollisionSystem::operator=(const game_engine::CollisionSystem &collisionSystem)
{
    _player = collisionSystem._player;
    _powerUp = collisionSystem._powerUp;
    _objectAndEnemy = collisionSystem._objectAndEnemy;
    return (*this);
}

void game_engine::CollisionSystem::collisionSystem()
{
    _player = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    _powerUp = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::POWERUP}, _entities);
    _objectAndEnemy = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMYALIEN,
        game_engine::EntitiesType::ENEMYBATTLESHIP, game_engine::EntitiesType::ENEMYTROOPER,
        game_engine::EntitiesType::STAGEOBSTACLE, game_engine::EntitiesType::DESTROYABLETILE}, _entities);
    collideAll();
}

void game_engine::CollisionSystem::collideAll()
{
    std::vector<std::shared_ptr<IEntities>>::iterator playerIter;
    std::vector<std::shared_ptr<AComponents>> playerComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator playerComponentIter;

    Transform *transfromComponent;
    Collision *collisionComponent;

    std::vector<std::shared_ptr<IEntities>>::iterator powerUpIter;
    std::vector<std::shared_ptr<AComponents>> powerUpComponent;
    for (playerIter = _player->begin(); playerIter != _player->end(); playerIter++) {
        playerComponent = playerIter->get()->getComponentList();
        for (playerComponentIter = playerComponent.begin(); playerComponentIter != playerComponent.end(); playerComponentIter++) {
            if (playerComponentIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(playerComponentIter->get());
            if (playerComponentIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(playerComponentIter->get());
        }
        for (powerUpIter = _powerUp->begin(); powerUpIter != _powerUp->end(); powerUpIter++) {
            powerUpComponent = powerUpIter->get()->getComponentList();
            if (collisionWithPowerUp(*transfromComponent, *collisionComponent, powerUpComponent) == true) {
                PowerUp *powerUpEntitie = static_cast<PowerUp *>(powerUpIter->get());
                Player *playerEntitie = static_cast<Player *>(playerIter->get());
                powerUpEntitie->activePowerUp(*playerEntitie);
                _powerUp->erase(powerUpIter);
            }
        }
    }
    ennemyCollisionSystem();
}

void game_engine::CollisionSystem::ennemyCollisionSystem()
{
    Transform *transfromComponent;
    Collision *collisionComponent;

    std::vector<std::shared_ptr<IEntities>>::iterator ennemyIter;
    std::vector<std::shared_ptr<AComponents>> ennemyComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator ennemyComponentIter;

    std::vector<std::shared_ptr<IEntities>>::iterator objectIter;
    std::vector<std::shared_ptr<AComponents>> objectComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator objectComponentIter;

    for (ennemyIter = _objectAndEnemy->begin(); ennemyIter != _objectAndEnemy->end(); ennemyIter++) {
       if (EntitiesParser::isAnEnemy(ennemyIter->get()->getEntitiesID())) {
           ennemyComponent = ennemyIter->get()->getComponentList();
            for (ennemyComponentIter = ennemyComponent.begin(); ennemyComponentIter != ennemyComponent.end(); ennemyComponentIter++) {
                if (ennemyComponentIter->get()->getType() == ComponentType::TRANSFORM)
                    transfromComponent = static_cast<Transform *>(ennemyComponentIter->get());
                if (ennemyComponentIter->get()->getType() == ComponentType::COLLISION)
                    collisionComponent = static_cast<Collision *>(ennemyComponentIter->get());
            }
            for (objectIter = _objectAndEnemy->begin(); objectIter != _objectAndEnemy->begin(); objectIter++) {
                objectComponent = objectIter->get()->getComponentList();
                if (ennemyCollisionWithObject(*transfromComponent, *collisionComponent, objectComponent)) {
                    transfromComponent->resetToOldPosition();
                    std::cout << "move ennemy to old" << std::endl;
                }
            }
        }
    }
}

bool game_engine::CollisionSystem::ennemyCollisionWithObject(Transform &ennemyTransfromComponent,
    Collision &ennemyCollisionComponent, std::vector<std::shared_ptr<AComponents>> objectComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator objectComponentIter;
    Transform *transfromComponent;
    Collision *collisionComponent;

    for (objectComponentIter = objectComponent.begin(); objectComponentIter != objectComponent.end(); objectComponentIter++) {
        if (objectComponentIter->get()->getType() == ComponentType::TRANSFORM)
            transfromComponent = static_cast<Transform *>(objectComponentIter->get());
        if (objectComponentIter->get()->getType() == ComponentType::COLLISION)
            collisionComponent = static_cast<Collision *>(objectComponentIter->get());
    }
    if (checkCollision(ennemyTransfromComponent, ennemyCollisionComponent, *transfromComponent, *collisionComponent))
        return (true);
    return (false);
}

bool game_engine::CollisionSystem::collisionWithPowerUp(Transform &playerTransfromComponent,
                                                        Collision &playerCollisionComponent, std::vector<std::shared_ptr<AComponents>> powerUpComponent)
{
    std::vector<std::shared_ptr<AComponents>>::iterator powerUpComponentIter;
    Transform *powerUpdTransfromComponent;
    Collision *powerUpCollisionComponent;

    for (powerUpComponentIter = powerUpComponent.begin(); powerUpComponentIter != powerUpComponent.end(); ++powerUpComponentIter) {
        if (powerUpComponentIter->get()->getType() == ComponentType::TRANSFORM)
            powerUpdTransfromComponent = static_cast<Transform *>(powerUpComponentIter->get());
        if (powerUpComponentIter->get()->getType() == ComponentType::COLLISION)
            powerUpCollisionComponent = static_cast<Collision *>(powerUpComponentIter->get());
    }
    if (checkCollision(playerTransfromComponent, playerCollisionComponent, *powerUpdTransfromComponent, *powerUpCollisionComponent)) {
        return (true);
    }
    return (false);
}

bool game_engine::CollisionSystem::checkCollision(Transform &playerTransform, Collision &playerCollision,
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
