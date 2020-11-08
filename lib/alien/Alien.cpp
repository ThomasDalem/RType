/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Alien
*/

#include "Alien.hpp"

enemies::Alien::Alien(game_engine::Vector position) : game_engine::Enemy(position)
{
}

enemies::Alien::~Alien()
{
}

void enemies::Alien::pathEnemy()
{
    if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y < 0 &&
        this->getTransform()->getPosition().y >= 40)
        this->getTransform()->setNewDirection(game_engine::Vector(2, -2));
    else {
        if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y > 0 &&
            this->getTransform()->getPosition().y <= 1040)
            this->getTransform()->setNewDirection(game_engine::Vector(2, 2));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(2, -2));
    }
}

extern "C" enemies::Alien *entryPoint(game_engine::Vector position)
{
    return (new enemies::Alien(position));
}