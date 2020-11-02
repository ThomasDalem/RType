/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>

namespace game_engine {
    struct Vector {
        Vector(int _x, int _y)
        : x(_x),y(_y)
        {}
        int x;
        int y;
    };
}

#endif /* !VECTOR_HPP_ */

