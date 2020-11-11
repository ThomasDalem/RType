/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Trooper
*/

#include "Trooper.hpp"
#include "Rectangle.hpp"

enemies::Trooper::Trooper(game_engine::Vector position, int id) : game_engine::Enemy(position, id)
{
    //this->getRender()->setRect(game_engine::Rectangle(18, 68, 33, 30)); //r-typesheet20.gif
    _entitesID = game_engine::EntitiesType::ENEMYTROOPER;
}

enemies::Trooper::~Trooper()
{
}

void enemies::Trooper::enemyIA()
{
    this->getTransform()->setNewDirection(game_engine::Vector(-15, 0));
}

extern "C" enemies::Trooper *entryPoint(game_engine::Vector position, int id)
{
    return (new enemies::Trooper(position, id));
}