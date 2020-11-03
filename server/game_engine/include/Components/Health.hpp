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
#include "AComponents.hpp"

namespace game_engine
{
    class Health : public AComponents
    {
    public:
        Health(size_t _healthPoint_ct, bool _isDamageable)
            : healthPoint(_healthPoint_ct), isDamageable(_isDamageable)
        {
            type = ComponentType::HEALTH;
        }
        ~Health();
        size_t getHealthPoint() {return healthPoint;}
        bool getDamabeable() {return isDamageable;}

    private:
        size_t healthPoint;
        bool isDamageable;
    };
} // namespace game_engine

#endif /* !HEALTH_HPP_ */
