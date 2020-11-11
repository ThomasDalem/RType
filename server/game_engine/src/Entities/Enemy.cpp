/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Enemy
*/

#include "Enemy.hpp"

game_engine::Enemy::Enemy(Vector _position, int id)
{
    _uniqueID = id;
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 40, 40), false);
    //_render = std::make_shared<Render>("./path_to_ennemy sprite", Rectangle(0, 67, 33, 36));
    _render = std::make_shared<Render>("./resources/sprites/r-typesheet1.gif", Rectangle(338, 256, 13, 4));
    _deathSound = std::make_shared<Sound>("./path_to_ennemy_death_sound");
    //_entitesID = EntitiesType::ENEMY;
    _componentList.push_back(_transform);
    _componentList.push_back(_health);
    _componentList.push_back(_deathSound);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
    _fireChrono = std::chrono::high_resolution_clock::now();
}
