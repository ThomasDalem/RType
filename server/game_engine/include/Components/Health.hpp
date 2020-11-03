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
        Health(size_t healthPoint, bool isDamageable)
            : AComponents(ComponentType::HEALTH), _healthPoint(healthPoint), _isDamageable(isDamageable)
        {
            _type = ComponentType::HEALTH;
        }
        ~Health() {}
        size_t getHealthPoint() const { return _healthPoint; }
        bool getDamabeable() const { return _isDamageable; }

        void setIsDamageable(bool isDamageable) {_isDamageable = isDamageable;}

        void getDamage() {
            if (_isDamageable && _healthPoint > 0)
                _healthPoint--;
        }

    private:
        size_t _healthPoint;
        bool _isDamageable;
    };
} // namespace game_engine

#endif /* !HEALTH_HPP_ */
