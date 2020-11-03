/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Shoot
*/

#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include "../Vector.hpp"
#include "AComponents.hpp"
namespace game_engine
{
    class Shoot : public AComponents
    {
    public:
        Shoot(Vector shootDirection, float fireRate)
            : AComponents(ComponentType::SHOOT), _shootDirection(shootDirection), _fireRate(fireRate)
        {
            _type = ComponentType::SHOOT;
        }
        ~Shoot() {}
        Vector getRectSize() const {return _shootDirection;}
        float getFireRate() const {return _fireRate;}

        void setFireRate(float fireRate) {_fireRate = fireRate;}

    private:
        Vector _shootDirection;
        float _fireRate;
    };
} // namespace game_engine

#endif /* !SHOOT_HPP_ */
