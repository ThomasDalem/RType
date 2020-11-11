/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** BattleShip
*/

#include "BattleShip.hpp"
#include "Rectangle.hpp"

enemies::BattleShip::BattleShip(game_engine::Vector position, int id) : game_engine::Enemy(position, id)
{
    //this->getRender()->setRect(game_engine::Rectangle(0, 0, 65, 50)); //r-typesheet26.gif
    _entitesID = game_engine::EntitiesType::ENEMYBATTLESHIP;
    _collision = std::make_shared<game_engine::Collision>(game_engine::Rectangle(0, 0, 195, 150), true);
    _componentList.push_back(_collision);
}

enemies::BattleShip::~BattleShip()
{
}

void enemies::BattleShip::enemyIA()
{
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y < 0) {
        if (this->getTransform()->getPosition().y >= 70)
        this->getTransform()->setNewDirection(game_engine::Vector(-3, -6));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(-3, 6));
    } else {
        if (this->getTransform()->getPosition().y - this->getTransform()->getOldPosition().y > 0 &&
            this->getTransform()->getPosition().y <= 750)
            this->getTransform()->setNewDirection(game_engine::Vector(-3, 6));
        else
            this->getTransform()->setNewDirection(game_engine::Vector(-3, -6));
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - _fireChrono).count() >= 700) {
        _fireChrono = std::chrono::high_resolution_clock::now();
        inputBuffer.push_back(game_engine::InputEnum::SHOOTINPUT);
    }
}

extern "C" enemies::BattleShip *entryPoint(game_engine::Vector position, int id)
{
    return (new enemies::BattleShip(position, id));
}