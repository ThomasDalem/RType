/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** AComponents
*/

#ifndef ACOMPONENTS_HPP_
#define ACOMPONENTS_HPP_

namespace game_engine
{
    enum ComponentType {
        TRANSFORM,
        SOUND,
        HEALTH,
        SHOOT,
        COLLISION,
        RENDER,
    };
    class AComponents
    {
    public:
        AComponents();
        ~AComponents();
        ComponentType getType() const;
    protected:
        ComponentType type;
    };
} // namespace game_engine
#endif /* !ACOMPONENTS_HPP_ */
