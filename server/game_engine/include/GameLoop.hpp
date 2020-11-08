/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "MoveSystem.hpp"
#include "DamageSystem.hpp"
#include "CollisionSystem.hpp"
#include "SpawnSystem.hpp"
#include "DeathSystem.hpp"
#include "./DDLoader.hpp"
#include "EntitiesParser.hpp"

namespace game_engine
{
    class GameLoop
    {
    public:
        GameLoop(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities);
        ~GameLoop();
        void gameLoop();
        bool areTherePlayers();
    protected:
    private:
        MoveSystem moveSystem;
        DeathSystem deathSystem;
        CollisionSystem collisionSystem;
        DamageSystem damageSystem;
        SpawnSystem spawnSystem;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
    };
} // namespace game_engine

#endif /* !GAMELOOP_HPP_ */
