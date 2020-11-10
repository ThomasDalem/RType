/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <cstdio>
#include <ctime>
#include <dirent.h>
#include "Components/Collision.hpp"
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "EntitiesEnum.hpp"
#include "Entities/IEntities.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"
#include "Entities/Bullet.hpp"
#include "Entities/PowerUp.hpp"
#include "Entities/StageObstacle.hpp"
#include "Entities/DestroyableTile.hpp"
#include "./DDLoader.hpp"
#include "EntitiesParser.hpp"

namespace game_engine
{
    class DeathSystem
    {
    public:
        DeathSystem();
        DeathSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities);
        ~DeathSystem();
        DeathSystem &operator=(const DeathSystem &deathSystem);
        void deathSystem();
        bool isDead(std::vector<std::shared_ptr<AComponents>> entitieComponent);
        void spawnPowerUp(game_engine::IEntities *entitie);

    protected:
    private:
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
    };
} // namespace game_engine

#endif /* !DEATHSYSTEM_HPP_ */
