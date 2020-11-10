/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Alien
*/

#include "Alien.hpp"
#include "Rectangle.hpp"
#include "Render.hpp"

enemies::Alien::Alien(game_engine::Vector position, int id) : game_engine::Enemy(position, id)
{
    //_render = std::make_shared<game_engine::Render>("./path_to_ennemy sprite", game_engine::Rectangle(0, 67, 33, 36)); //r-typesheet18.gif
    _entitesID = game_engine::EntitiesType::ENEMYALIEN;
    //_componentList.push_back(_render);
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

extern "C" enemies::Alien *entryPoint(game_engine::Vector position, int id)
{
    return (new enemies::Alien(position, id));
}