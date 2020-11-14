/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "MoveSystem.hpp"
#include "./DDLoader.hpp"
#include "SpawnSystem.hpp"
#include "DeathSystem.hpp"
#include "DamageSystem.hpp"
#include "EntitiesParser.hpp"
#include "CollisionSystem.hpp"
#include "../../include/NetUDPServer.hpp"
#include "../../include/NetTCPServer.hpp"

using namespace std;
namespace game_engine {
    class GameLoop {
        public:
            GameLoop(shared_ptr<vector<shared_ptr<IEntities>>> entities);
            ~GameLoop();

            void oneLoop(void);
            void gameLoop(void);
            void sendToClients(void);
            bool areTherePlayers(void);
            void sendEntitiesToClient(std::vector<std::shared_ptr<game_engine::IEntities>>::iterator entitiesListIter, 
                Transform *transfrom, Render *render);
            void sendHUDToClient();
            void respondToConnection(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message);
            void getComponentToDisp(vector<shared_ptr<AComponents>> componentList, Transform *transfromComponent, Render *collisionComponent);

        private:
            MoveSystem moveSystem;
            SpawnSystem spawnSystem;
            DeathSystem deathSystem;
            DamageSystem damageSystem;
            network::NetUDPServer server;
            CollisionSystem collisionSystem;
            // network::NetTCPServerClient serverTCP;
            shared_ptr<vector<shared_ptr<IEntities>>> _entities;

        protected:
    };
}

#endif
