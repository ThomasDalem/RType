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
#include "Entities/StageObstacle.hpp"
#include "Entities/DestroyableTile.hpp"
#include "./DDLoader.hpp"
#include "EntitiesParser.hpp"


namespace game_engine
{
    class SpawnSystem
    {
    public:
        SpawnSystem();
        SpawnSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities);
        ~SpawnSystem();
        SpawnSystem &operator=(const SpawnSystem &deathSystem);
        void spawnSystem();
        void spawnEnemy();
        void newPlayer(int clientID);
        void checkEntitieShoot();
        void checkPlayerShoot(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListPlayer);
        void checkEnnemyShoot(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListEnnemy, std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListPlayer);

        void spawnObstacle();
        void addObstacle();
        int getAndIncID();
        int getID() const;
        void incID();

    protected:
    private:
        std::clock_t blockSpawnClock;
        double blockSpawnTime;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
        std::vector<DDloader<game_engine::Enemy>> _enemyLoader;
        int id;
    };
} // namespace game_engine

#endif /* !SPAWNSYSTEM_HPP_ */
