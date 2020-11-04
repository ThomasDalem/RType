/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

game_engine::CollisionSystem::CollisionSystem(std::vector<std::shared_ptr<IEntities>> &player, std::vector<std::shared_ptr<IEntities>> &powerUp, std::vector<std::shared_ptr<IEntities>> &objectAndEnnemy)
    : _player(player), _powerUp(powerUp), _objectAndEnnemy(objectAndEnnemy)
{
}

game_engine::CollisionSystem::~CollisionSystem()
{
}

void game_engine::CollisionSystem::collisionSystem()
{
    std::vector<std::shared_ptr<IEntities>>::iterator playerIter;
    std::vector<std::shared_ptr<AComponents>> playerComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator playerComponentIter;

    Transform *transfromComponent;
    Collision *collisionComponent;
    Transform *transfromComponent2;
    Collision *collisionComponent2;

    std::vector<std::shared_ptr<IEntities>>::iterator powerUpIter;
    std::vector<std::shared_ptr<AComponents>> powerUpComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator powerUpComponentIter;

    std::vector<std::shared_ptr<IEntities>>::iterator objectAndEnnemyIter;
    std::vector<std::shared_ptr<AComponents>> objectAndEnnemyComponent;
    std::vector<std::shared_ptr<AComponents>>::iterator objectAndEnnemyComponentIter;

   /*for (objectAndEnnemyIter = _objectAndEnnemy.begin(); objectAndEnnemyIter != _objectAndEnnemy.end(); objectAndEnnemyIter++) {
        for (objectAndEnnemyComponentIter = _objectAndEnnemyComponent.begin(); objectAndEnnemyComponentIter != _objectAndEnnemyComponent.end(); objectAndEnnemyComponentIter++) {
            if (objectAndEnnemyComponentIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(objectAndEnnemyComponentIter->get());
            if (objectAndEnnemyComponentIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(objectAndEnnemyComponentIter->get());
        }
        for (objectAndEnnemyIter2 = objectAndEnnemyIter; objectAndEnnemyIter2 != _objectAndEnnemy2.end(); objectAndEnnemyIter2++) {
            for (objectAndEnnemyComponentIter = _objectAndEnnemyComponent.begin(); objectAndEnnemyComponentIter != _objectAndEnnemyComponent.end(); objectAndEnnemyComponentIter++) {
                if (objectAndEnnemyComponentIter->get()->getType() == ComponentType::TRANSFORM)
                    transfromComponent = static_cast<Transform *>(objectAndEnnemyComponentIter->get());
                if (objectAndEnnemyComponentIter->get()->getType() == ComponentType::COLLISION)
                    collisionComponent = static_cast<Collision *>(objectAndEnnemyComponentIter->get());
            }
            for (parse = iter; parse != map.end(); ++parse) {
                if (iter->first == EntitiesType::ENNEMY && parse->first != EntitiesType::PLAYER &&
                    parse->first != EntitiesType::POWERUP) //&& checkCollision(iter->second, parse->second) == true)
                    iter->second.first.get()->resetToOldPosition();
        }
    }*/
    for (playerIter = _player.begin(); playerIter != _player.end(); playerIter++)
    {
        playerComponent = playerIter->get()->getComponentList();
        for (playerComponentIter = playerComponent.begin(); playerComponentIter != playerComponent.end(); playerComponentIter++)
        {
            if (playerComponentIter->get()->getType() == ComponentType::TRANSFORM)
                transfromComponent = static_cast<Transform *>(playerComponentIter->get());
            if (playerComponentIter->get()->getType() == ComponentType::COLLISION)
                collisionComponent = static_cast<Collision *>(playerComponentIter->get());
        }
        for (powerUpIter = _powerUp.begin(); powerUpIter != _powerUp.end(); powerUpIter++)
        {
            //powerUpComponent = powerUpIter->get()->getComponentList();
            /*if (iter->first == EntitiesType::PLAYER && parse->first == EntitiesType::POWERUP &&
                checkCollision(iter->second, parse->second) == true)
                printf("Power up touché");// Je sais pas;
            }*/
            //if (checkCollisionWith(transfromComponent, collisionComponent, objectComponent) == true)
            //    healthComponent->getDamage();
        }
    }
}

/*bool game_engine::CollisionSystem::checkCollision(std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect1, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect2)
{
    Vector end_pos_rect1 = Vector((rect1.first->getPosition().x + rect1.second->getRectSize().L), (rect1.first->getPosition().y + rect1.second->getRectSize().l));
    Vector end_pos_rect2 = Vector((rect2.first->getPosition().x + rect2.second->getRectSize().L), (rect2.first->getPosition().y + rect2.second->getRectSize().l));

    if (rect1.first->getPosition().x >= rect2.first->getPosition().x && rect1.first->getPosition().x <= end_pos_rect2.x &&
        rect1.first->getPosition().y >= rect2.first->getPosition().y && rect1.first->getPosition().y <= end_pos_rect2.y)
        return (true);
    if (rect1.first->getPosition().x >= rect2.first->getPosition().x && rect1.first->getPosition().x <= end_pos_rect2.x &&
        end_pos_rect1.y >= rect2.first->getPosition().y && end_pos_rect1.y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect1.x >= rect2.first->getPosition().x && end_pos_rect1.x <= end_pos_rect2.x &&
        rect1.first->getPosition().y >= rect2.first->getPosition().y && rect1.first->getPosition().y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect1.x >= rect2.first->getPosition().x && end_pos_rect1.x <= end_pos_rect2.x &&
        end_pos_rect1.y >= rect2.first->getPosition().y && end_pos_rect1.y <= end_pos_rect2.y)
        return (true);
    if (end_pos_rect2.x >= rect1.first->getPosition().x && end_pos_rect2.x <= end_pos_rect1.x &&
        end_pos_rect2.y >= rect1.first->getPosition().y && end_pos_rect2.y <= end_pos_rect1.y)
        return (true);
    return (false);
}*/