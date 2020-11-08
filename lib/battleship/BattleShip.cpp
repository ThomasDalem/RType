/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** BattleShip
*/

#include "BattleShip.hpp"

enemies::BattleShip::BattleShip(game_engine::Vector position) : game_engine::Enemy(position)
{
}

enemies::BattleShip::~BattleShip()
{
}

void enemies::BattleShip::pathEnemy()
{
    if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y < 0 &&
        this->getTransform()->getPosition().y >= 40)
        this->getTransform()->setNewDirection(game_engine::Vector(0, -2));
    else {
        if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y > 0 &&
            this->getTransform()->getPosition().y <= 1040)
            this->getTransform()->setNewDirection(game_engine::Vector(0, 2));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(0, -2));
    }
}

extern "C" enemies::BattleShip *entryPoint(game_engine::Vector position)
{
    return (new enemies::BattleShip(position));
}