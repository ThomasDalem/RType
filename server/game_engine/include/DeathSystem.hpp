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

namespace game_engine {
    class DeathSystem {
        public:
            DeathSystem();
            DeathSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities);
            ~DeathSystem();
            void disconnectClient(boost::asio::ip::udp::endpoint clientEndpoint, network::NetUDPServer &server);
            void deathSystem(network::NetUDPServer &server);
            void spawnPowerUp(game_engine::IEntities *entitie);
            void incScoreForAllPlayer();
            DeathSystem &operator=(const DeathSystem &deathSystem);
            bool checkGameBorder(Transform &transform, Collision &collision);
            bool isDead(std::vector<std::shared_ptr<AComponents>> entitieComponent);
            void deadClient(std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEntitieIter, network::NetUDPServer &server);

        protected:
        private:
            std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
    };
} // namespace game_engine

#endif /* !DEATHSYSTEM_HPP_ */
