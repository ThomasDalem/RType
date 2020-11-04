/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SpawnSystem
*/

#ifndef SPAWNSYSTEM_HPP_
#define SPAWNSYSTEM_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include<dirent.h>
#include "Components/Collision.hpp"
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "EntitiesEnum.hpp"
#include "Entities/IEntities.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"
#include "./DDLoader.hpp"


namespace game_engine
{
    class SpawnSystem
    {
    public:
        SpawnSystem(std::vector<std::shared_ptr<IEntities>> &entities);
        ~SpawnSystem();
        void loadEnnemyLibrary();
        void spawnEnnemy();
        void newPlayer(int clientID);

    protected:
    private:
        std::vector<std::shared_ptr<IEntities>> &_entities;
    };
} // namespace game_engine

#endif /* !SPAWNSYSTEM_HPP_ */
