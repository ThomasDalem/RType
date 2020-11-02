/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** PowerUp
*/

#include "PowerUp.hpp"

game_engine::PowerUp::PowerUp(Vector _position)
{
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 50, 50), false);
    _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 0, 50, 50));
    _sound = std::make_shared<Sound>("./path_to_powerUp_sound");
    _entitesID = EntitiesType::PowerUp;
}
