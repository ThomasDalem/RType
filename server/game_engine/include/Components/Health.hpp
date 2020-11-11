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
#include <unordered_map>
#include <string>
#include <fstream>
#include "AComponents.hpp"

namespace game_engine
{
    class Health : public AComponents
    {
    public:
        Health()
            : AComponents(ComponentType::HEALTH), _healthPoint(1), _isDamageable(true)
        {
            _type = ComponentType::HEALTH;
        }
        Health(int healthPoint, bool isDamageable)
            : AComponents(ComponentType::HEALTH), _healthPoint(healthPoint), _isDamageable(isDamageable)
        {
            _type = ComponentType::HEALTH;
        }
        ~Health() {}
        int getHealthPoint() const { return _healthPoint; }
        bool getDamabeable() const { return _isDamageable; }

        void setHealthPoint(int healthPoint) {_healthPoint = healthPoint;}
        void setIsDamageable(bool isDamageable) {_isDamageable = isDamageable;}

        void getDamage() {
            if (_isDamageable && _healthPoint > 0)
                _healthPoint--;
        }

    private:
        int _healthPoint = 1;
        bool _isDamageable = true;
    };
} // namespace game_engine

#endif /* !HEALTH_HPP_ */
