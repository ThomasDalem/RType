/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "../Vector.hpp"
#include "AComponents.hpp"

namespace game_engine
{
    class Transform : public AComponents
    {
    public:
        Transform(Vector position_ct, float rotation_ct, Vector direction_ct)
            : position(position_ct), rotation(rotation_ct), direction(direction_ct), oldPosition(position_ct)
        {
            type = ComponentType::TRANSFORM;
        }
        ~Transform() {};
        Vector getOldPosition() const {return oldPosition;}
        Vector getPosition() const {return position;}
        float getRotation() const {return rotation;}
        Vector getDirection() const {return direction;}

        void setOldPosition(Vector newOldPosition) {oldPosition = newOldPosition;}
        void changeDirection(Vector newDirection) {direction = newDirection;}
        void applyDirection(Vector _direction) {
            position.x += _direction.x;
            position.y += _direction.y;
        }
        void setRotation(float newRotation) {rotation = newRotation;}
    private:
        Vector oldPosition;
        Vector position;
        float rotation;
        Vector direction;
    };
} // namespace game_engine

#endif /* !TRANSFORM_HPP_ */