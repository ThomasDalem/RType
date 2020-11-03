/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DestroyableTile
*/

#include "DestroyableTile.hpp"

game_engine::DestroyableTile::DestroyableTile(Vector _position)
{
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 100, 50), true);
    _render = std::make_shared<Render>("./path_to_destroyable_tiles sprite", Rectangle(0, 0, 100, 50));
    _deathSound = std::make_shared<Sound>("./path_to_destoryable_tiles_death_sound");
    _entitesID = EntitiesType::DestroyableTile;
}
