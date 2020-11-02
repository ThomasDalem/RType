/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <iostream>

namespace game_engine {
    struct Rectangle
    {
        Rectangle(size_t _x, size_t _y, size_t _L, size_t _l)
        : x(_x), y(_y), L(_L), l(_l)
        {}
        size_t x;
        size_t y;
        size_t L;
        size_t l;
    };
}

#endif /* !RECTANGLE_HPP_ */

