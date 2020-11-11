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

void enemies::Alien::enemyIA()
{
    double timePassed = difftime(time(0), _fireTimer) * 1000.0;

    if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y < 0) {
        if (this->getTransform()->getPosition().y >= 70)
            this->getTransform()->setNewDirection(game_engine::Vector(-5, -3));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(-5, 3));
    } else {
        if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y > 0 &&
            this->getTransform()->getPosition().y <= 750)
            this->getTransform()->setNewDirection(game_engine::Vector(-5, 3));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(-5, -3));
    }
    if (timePassed >= 550) {
        _fireTimer = time(0);
        inputBuffer.push_back(game_engine::InputEnum::SHOOTINPUT);
    }
}

extern "C" enemies::Alien *entryPoint(game_engine::Vector position, int id)
{
    return (new enemies::Alien(position, id));
}