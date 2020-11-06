/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Trooper
*/

#include "Trooper.hpp"

enemies::Trooper::Trooper(game_engine::Vector position) : game_engine::Enemy(position)
{
}

enemies::Trooper::~Trooper()
{
}

void enemies::Trooper::pathEnemy()
{
    this->getTransform()->setNewDirection(game_engine::Vector(0, 2));
}

extern "C" enemies::Trooper *entryPoint(game_engine::Vector position)
{
    return (new enemies::Trooper(position));
}