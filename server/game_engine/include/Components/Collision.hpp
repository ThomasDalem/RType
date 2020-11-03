/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Collision
*/

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include "../Rectangle.hpp"
#include "AComponents.hpp"

namespace game_engine
{
    class Collision : public AComponents
    {
    public:
        Collision(Rectangle rectSize, bool damagePlayer)
            : AComponents(ComponentType::COLLISION), _rectSize(rectSize), _damagePlayer(damagePlayer)
        {
            _type = ComponentType::COLLISION;
        }
        ~Collision() {};
        Rectangle getRectSize() const {return _rectSize;}
        bool getCanDamagePlayer() const {return _damagePlayer;}

    private:
        Rectangle _rectSize;
        bool _damagePlayer;
    };
} // namespace game_engine

#endif /* !COLLISION_HPP_ */
