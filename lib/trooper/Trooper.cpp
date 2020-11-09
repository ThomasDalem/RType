/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Trooper
*/

#include "Trooper.hpp"

enemies::Trooper::Trooper(game_engine::Vector position, int id) : game_engine::Enemy(position, id)
{
}

enemies::Trooper::~Trooper()
{
}

void enemies::Trooper::pathEnemy()
{
    this->getTransform()->setNewDirection(game_engine::Vector(2, 0));
}

extern "C" enemies::Trooper *entryPoint(game_engine::Vector position, int id)
{
    return (new enemies::Trooper(position, id));
}