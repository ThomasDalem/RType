/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Collision
*/

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include "../Rectangle.hpp"

namespace game_engine {
    struct Collision
    {
        Collision(Rectangle rectSize_ct, bool damagePlayer_ct)
        : rectSize(rectSize_ct), damagePlayer(damagePlayer_ct)
        {}

        Rectangle rectSize;
        bool damagePlayer;
    };
}

#endif /* !COLLISION_HPP_ */
