/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DestroyableTile
*/

#include "DestroyableTile.hpp"

game_engine::DestroyableTile::DestroyableTile(Vector _position, int id)
{
    _uniqueID = id;
    _transform = std::make_shared<Transform>(_position, 0, Vector(-5, 0));
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 40, 40), true);
    _render = std::make_shared<Render>("./path_to_destroyable_tiles sprite", Rectangle(52, 26, 149, 139));
    _deathSound = std::make_shared<Sound>("./path_to_destoryable_tiles_death_sound");
    _entitesID = EntitiesType::DESTROYABLETILE;
    _componentList.push_back(_transform);
    _componentList.push_back(_health);
    _componentList.push_back(_deathSound);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
}
