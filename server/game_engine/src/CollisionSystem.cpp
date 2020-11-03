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

game_engine::CollisionSystem::~CollisionSystem()
{
}

void game_engine::CollisionSystem::collisionSystem(std::map<EntitiesType, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>>> map)
{
    std::map<EntitiesType, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>>>::iterator iter;
    std::map<EntitiesType, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>>>::iterator parse;

    for (iter = map.begin(); iter != map.end(); ++iter) {
        for (parse = iter; parse != map.end(); ++parse) {
            if (iter->first == EntitiesType::ENNEMY && parse->first != EntitiesType::PLAYER &&
                parse->first != EntitiesType::POWERUP && checkCollision(iter->second, parse->second) == true)
                iter->second.first.get()->resetToOldPosition();
            if (iter->first == EntitiesType::PLAYER && parse->first == EntitiesType::POWERUP &&
                checkCollision(iter->second, parse->second) == true)
                printf("Power up touché");// Je sais pas;
        }
    }
}

bool game_engine::CollisionSystem::checkCollision(std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect1, std::pair<std::shared_ptr<Transform>, std::shared_ptr<Collision>> rect2)
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
}