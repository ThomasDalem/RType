/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

game_engine::Player::Player(Vector _position, PlayerColor playerColor)
{
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 4, 4), false);
    _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 0, 75, 45));
    _deathSound = std::make_shared<Sound>("./path_to_death_sound");
    _entitesID = EntitiesType::PLAYER;
    _invincibility = 0;
    _speedMultiplicator = 1;
}
