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
        Transform(Vector position, float rotation, Vector direction)
            : AComponents(ComponentType::TRANSFORM), _position(position), _rotation(rotation), _direction(direction), _oldPosition(Vector(0, 0))
        {
            _type = ComponentType::TRANSFORM;
        }
        ~Transform() {};
        Vector getOldPosition() const {return _oldPosition;}
        Vector getPosition() const {return _position;}
        float getRotation() const {return _rotation;}
        Vector getDirection() const {return _direction;}

        void setOldPosition(Vector newOldPosition) {_oldPosition = newOldPosition;}
        void changeDirection(Vector newDirection) {_direction = newDirection;}
        void applyDirection(Vector direction) {
            _position.x += direction.x;
            _position.y += direction.y;
        }
        void setRotation(float newRotation) {_rotation = newRotation;}
        void setNewDirection(Vector newDirection) {_direction = newDirection;}

        void resetToOldPosition() {
            _position.x = _oldPosition.x;
            _position.y = _oldPosition.y;
        };

    private:
        Vector _oldPosition;
        Vector _position;
        float _rotation;
        Vector _direction;
    };
} // namespace game_engine

#endif /* !TRANSFORM_HPP_ */