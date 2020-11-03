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
            : AComponents(ComponentType::HEALTH), healthPoint(_healthPoint_ct), isDamageable(_isDamageable)
        {
            //type = ComponentType::HEALTH;
        }
        ~Health() {}
        size_t getHealthPoint() const { return healthPoint; }
        bool getDamabeable() const { return isDamageable; }
        void getDamage() {
            if (isDamageable)
                healthPoint--;
        }

    private:
        size_t healthPoint;
        bool isDamageable;
    };
} // namespace game_engine

#endif /* !HEALTH_HPP_ */
