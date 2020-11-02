/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include <iostream>
#include <map>
#include <memory>
#include "Components/Transform.hpp"
#include "EntitiesEnum.hpp"

namespace game_engine
{
    class MoveSystem
    {
    public:
        MoveSystem();
        ~MoveSystem();
        void moveSystem(std::map<int, std::shared_ptr<Transform>> map);

    protected:
    private:
    };
} // namespace game_engine

#endif /* !MOVESYSTEM_HPP_ */
