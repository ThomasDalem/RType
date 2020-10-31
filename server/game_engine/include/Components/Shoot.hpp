/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Shoot
*/

#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include "../Vector.hpp"

namespace game_engine {
    struct Shoot
    {
        Shoot(Vector shootDirection_ct, float fireRate_ct)
        : shootDirection(shootDirection_ct), fireRate(fireRate_ct)
        {}

        Vector shootDirection;
        float fireRate;
    };
}

#endif /* !SHOOT_HPP_ */
