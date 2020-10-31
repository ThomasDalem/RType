/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <unordered_map>
#include <string>
#include <fstream>

namespace game_engine {
    struct Health
    {
        Health(size_t healthPoint_ct)
        : healthPoint(healthPoint_ct)
        {}

        size_t healthPoint;
    };
}

#endif /* !HEALTH_HPP_ */
