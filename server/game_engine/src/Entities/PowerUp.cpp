/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** PowerUp
*/

#include "PowerUp.hpp"

game_engine::PowerUp::PowerUp(Vector _position)
{
    _powerUpType = static_cast<PowerUpType>(rand() % PowerUpType::SHIELD + 1);

    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(-5, 0));
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 60, 60), false);
    _render = std::make_shared<Render>("./resources/sprites/block.png", Rectangle(39, 0, 20, 20));
    _sound = std::make_shared<Sound>("./path_to_powerUp_sound");
    _health = std::make_shared<Health>(1, true);
    _entitesID = EntitiesType::POWERUP;
    _componentList.push_back(_transform);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
    _componentList.push_back(_sound);
    _componentList.push_back(_health);
}

void game_engine::PowerUp::activePowerUp(game_engine::Player &player)
{
    if (_powerUpType == PowerUpType::INCREASEFIRERATE)
        activeIncreaseFireRate(player);
    if (_powerUpType == PowerUpType::SHIELD)
        activeSheild(player);
    if (_powerUpType == PowerUpType::SPEEDBOOST)
        activeSpeedBoost(player);
}

#include "Player.hpp"

void game_engine::PowerUp::activeIncreaseFireRate(game_engine::Player &player)
{
    player.getShoot()->setFireRate(player.getShoot()->getFireRate() + 1);
}

void game_engine::PowerUp::activeSheild(game_engine::Player &player)
{
    player.getHealth()->setIsDamageable(false);
    player.setTimeInvincibility(player.getTimeInvincibility() + 1000);
}

void game_engine::PowerUp::activeSpeedBoost(game_engine::Player &player)
{
    player.setSpeedMultiplicator(player.getSpeedMultiplicator() + 1);
}
