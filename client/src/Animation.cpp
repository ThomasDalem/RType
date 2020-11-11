/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Animation
*/

#include "Animation.hpp"

client::Animation::Animation()
{
    _clock.restart();
}

client::Animation::~Animation()
{
}

bool client::Animation::checkTimerAnimation() {
    sf::Time time;
    float seconds = 0;

    time = _clock.getElapsedTime();
    seconds = time.asMicroseconds() / 300000.0;
    if (seconds > 1) {
        _clock.restart();
        return (true);
    }
    return (false);
}

void client::Animation::updateAnimation(vector<shared_ptr<Entities>> &entities)
{
    for (size_t i = 0; i < entities.size(); i ++) {
        switch(entities[i]->getEntityType()) {
            case 0: updateImageRect(entities[i], 64, 0); break; // Player
            case 7: updateImageRect(entities[i], 97, 0); break; // Alien
            case 8: updateImageRect(entities[i], 127, 0); break; // Battleshipe
            case 9: updateImageRect(entities[i], 80, 18); break; // Trooper
        }
    }
}

void client::Animation::updateImageRect(shared_ptr<Entities> &entitie, int max_left, int min_left)
{
    sf::IntRect rect = entitie->getImage()->getRectangleSheep();

    if (rect.left <= max_left)
        rect.left += rect.width;
    else
        rect.left = min_left;
    entitie->getImage()->setRectangleSheep(rect);
}