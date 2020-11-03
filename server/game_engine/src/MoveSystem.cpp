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

bool game_engine::MoveSystem::checkGameBorder(Transform &transform)
{
    if (transform.getPosition().y + transform.getDirection().y < 0 ||
        transform.getPosition().y + transform.getDirection().y > 1080)
        return (true);
    return (false);
}