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
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 50, 50), false);
    _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 0, 50, 50));
    _sound = std::make_shared<Sound>("./path_to_powerUp_sound");
    _entitesID = EntitiesType::POWERUP;
    _componentList.push_back(_transform);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
    _componentList.push_back(_sound);
}

void game_engine::PowerUp::ActivePowerUp(std::shared_ptr<game_engine::Player> player)
{
    if (_powerUpType == PowerUpType::INCREASEFIRERATE)
        activeIncreaseFireRate(player);
    if (_powerUpType == PowerUpType::SHIELD)
        activeSheild(player);
    if (_powerUpType == PowerUpType::SPEEDBOOST)
        activeSpeedBoost(player);
}

#include "Player.hpp"

void game_engine::PowerUp::activeIncreaseFireRate(std::shared_ptr<game_engine::Player> player)
{
    player.get()->getShoot()->setFireRate(player.get()->getShoot()->getFireRate() + 1);
}

void game_engine::PowerUp::activeSheild(std::shared_ptr<game_engine::Player> player)
{
    player.get()->getHealth()->setIsDamageable(false);
    player.get()->setTimeInvincibility(player.get()->getTimeInvincibility() + 1000);
}

void game_engine::PowerUp::activeSpeedBoost(std::shared_ptr<game_engine::Player> player)
{
    player.get()->setSpeedMultiplicator(player.get()->getSpeedMultiplicator() + 1);
}
