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
#include <vector>
#include "./Components/Transform.hpp"
#include "EntitiesEnum.hpp"
#include "Entities/IEntities.hpp"

namespace game_engine
{
    class MoveSystem
    {
    public:
        MoveSystem(std::vector<std::shared_ptr<IEntities>> &list);
        ~MoveSystem();
        void moveSystem();
        bool checkGameBorder(Transform &transform);

    protected:
    private:
        std::vector<std::shared_ptr<IEntities>> &_list;
        //std::map<int, std::tuple<EntitiesType, std::shared_ptr<Transform>>> _map;
    };
} // namespace game_engine

#endif /* !MOVESYSTEM_HPP_ */
