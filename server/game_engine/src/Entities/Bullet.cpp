/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Bullet
*/

#include <memory>
#include "Bullet.hpp"
#include "./Components/Transform.hpp"
#include "./Components/Sound.hpp"

game_engine::Bullet::Bullet(bool _damagePlayer, Vector _direction, Vector _position, int id)
{
    _uniqueID = id;
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, _direction);
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 4, 4), _damagePlayer);
    _render = std::make_shared<Render>("./path_to_bullet sprite", Rectangle(0, 0, 5, 5));
    _fireSound = std::make_shared<Sound>("./path_to_fire_sound");
    _entitesID = EntitiesType::BULLET;
    _componentList.push_back(_transform);
    _componentList.push_back(_fireSound);
    _componentList.push_back(_health);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
}