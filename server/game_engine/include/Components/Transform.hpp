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
        Transform(Vector position_ct, float rotation_ct, Vector direction_ct)
        : position(position_ct), rotation(rotation_ct), direction(direction_ct), oldPosition(position_ct)
        {}
        Vector oldPosition;
        Vector position;
        float rotation;
        Vector direction;
    };
}

#endif /* !TRANSFORM_HPP_ */