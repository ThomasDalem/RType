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
        Rectangle(int _x, int _y, int _L, int _l)
        : x(_x), y(_y), L(_L), l(_l)
        {}
        int x;
        int y;
        int L;
        int l;
    };
}

#endif /* !RECTANGLE_HPP_ */

