/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** MoveSystem
*/
//bite
#include "MoveSystem.hpp"

game_engine::MoveSystem::MoveSystem(std::vector<std::shared_ptr<IEntities>> &list): _list(list)
{
}

game_engine::MoveSystem::~MoveSystem()
{
}

void game_engine::MoveSystem::moveSystem()
{
    std::vector<std::shared_ptr<IEntities>>::iterator iter;
    std::vector<std::shared_ptr<AComponents>> entitieComponent;

    for (iter = _list.begin(); iter != _list.end(); ++iter) {
        entitieComponent = iter->get()->getComponentList();
        std::vector<std::shared_ptr<AComponents>>::iterator componentIter;
        for (componentIter = entitieComponent.begin(); componentIter != entitieComponent.end(); ++componentIter) {
            if (componentIter->get()->getType() == ComponentType::TRANSFORM) {
                Transform *transfromComponent = static_cast<Transform *>(componentIter->get());
                if (checkGameBorder(*transfromComponent) != true) {
                    transfromComponent->setOldPosition(transfromComponent->getPosition());
                    transfromComponent->applyDirection(transfromComponent->getDirection());
                }
            }
        }
    }
}


void game_engine::MoveSystem::applyMovement()
{
    std::vector<std::shared_ptr<game_engine::IEntities>> newListPlayer;
    std::vector<std::shared_ptr<game_engine::IEntities>> newListEnnemy;

    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _list, newListPlayer);
    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMY}, _list, newListEnnemy);
    changePlayerDirection(newListPlayer);
    changeEnnemyDirection(newListEnnemy);
}

void game_engine::MoveSystem::changePlayerDirection(std::vector<std::shared_ptr<game_engine::IEntities>> newListPlayer)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    game_engine::Player *player;

    for (listPlayerIter = newListPlayer.begin(); listPlayerIter != newListPlayer.end(); listPlayerIter++) {
        player = static_cast<Player *>(listPlayerIter->get());
        if (player->getFirstEnum() != InputEnum::NOTHING && player->getFirstEnum() != InputEnum::SHOOTINPUT) {
            if (player->getFirstEnum() == InputEnum::MOVEDOWN)
                player->getTransform()->changeDirection(Vector(0, -5));
            if (player->getFirstEnum() == InputEnum::MOVEUP)
                player->getTransform()->changeDirection(Vector(0, 5));
            if (player->getFirstEnum() == InputEnum::MOVELEFT)
                player->getTransform()->changeDirection(Vector(-5, 0));
            if (player->getFirstEnum() == InputEnum::MOVERIGHT)
                player->getTransform()->changeDirection(Vector(5, 0));
            player->popFirstInput();
        }
        else
            player->getTransform()->changeDirection(Vector(0, 0));
    }
}
void game_engine::MoveSystem::changeEnnemyDirection(std::vector<std::shared_ptr<game_engine::IEntities>> newListEnnemy)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEnnemyIter;
    game_engine::Enemy *ennemy;

    for (listEnnemyIter = newListEnnemy.begin(); listEnnemyIter != newListEnnemy.end(); listEnnemyIter++) {
        ennemy = static_cast<Enemy *>(listEnnemyIter->get());
        if (ennemy->getFirstEnum() != InputEnum::NOTHING && ennemy->getFirstEnum() != InputEnum::SHOOTINPUT) {
            if (ennemy->getFirstEnum() == InputEnum::MOVEDOWN)
                ennemy->getTransform()->changeDirection(Vector(0, -5));
            if (ennemy->getFirstEnum() == InputEnum::MOVEUP)
                ennemy->getTransform()->changeDirection(Vector(0, 5));
            if (ennemy->getFirstEnum() == InputEnum::MOVELEFT)
                ennemy->getTransform()->changeDirection(Vector(-5, 0));
            if (ennemy->getFirstEnum() == InputEnum::MOVERIGHT)
                ennemy->getTransform()->changeDirection(Vector(5, 0));
            ennemy->popFirstInput();
        }
        else
            ennemy->getTransform()->changeDirection(Vector(0, 0));
    }
}


bool game_engine::MoveSystem::checkGameBorder(Transform &transform)
{
    if (transform.getPosition().y + transform.getDirection().y < 0 ||
        transform.getPosition().y + transform.getDirection().y > 1080 ||
        transform.getPosition().x + transform.getDirection().x > 1920 ||
        transform.getPosition().x + transform.getDirection().x < 0)
        return (true);
    return (false);
}