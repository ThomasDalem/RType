/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "../Vector.hpp"

namespace game_engine {
    struct Transform
    {
        Transform(Vector postion_ct, float rotation_ct, Vector direction_ct)
        : postion(postion_ct), rotation(rotation_ct), direction(direction_ct)
        {}

        Vector postion;
        float rotation;
        Vector direction;
    };
}

#endif /* !TRANSFORM_HPP_ */