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
        Collision(Rectangle rectSize_ct, bool damagePlayer_ct)
            : AComponents(ComponentType::COLLISION), rectSize(rectSize_ct), damagePlayer(damagePlayer_ct)
        {
            //type = ComponentType::COLLISION;
        }
        ~Collision() {};
        Rectangle getRectSize() {return rectSize;}
        bool getCanDamagePlayer() {return damagePlayer;}

    private:
        Rectangle rectSize;
        bool damagePlayer;
    };
} // namespace game_engine

#endif /* !COLLISION_HPP_ */
