/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** StageObstacle
*/

#include "StageObstacle.hpp"

game_engine::StageObstacle::StageObstacle(Vector _position, int id)
{
    _uniqueID = id;
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(-5, 0));
    _health = std::make_shared<Health>(1, false);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 40, 40), false);
    _render = std::make_shared<Render>("./path_to_obstacle sprite", Rectangle(20, 0, 20, 20));
    _entitesID = EntitiesType::STAGEOBSTACLE;
    _componentList.push_back(_transform);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
}
