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
#include "../../include/NetUDPServer.hpp"
#include "SafeQueue.hpp"

namespace game_engine
{
    class GameLoop
    {
    public:
        GameLoop(int roomNbr, SafeQueue<std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>>> &UDPMessages,
            SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &UDPMessagesToSend);
        ~GameLoop();
        void gameLoop();
        bool areTherePlayers();
        void sendToClients();
        void getComponentToDisp(std::vector<std::shared_ptr<AComponents>> componentList, Transform *transfromComponent, Render *collisionComponent);

    private:
        bool isNewClient(boost::asio::ip::udp::endpoint const& endpoint) const;
        void removeClient(boost::asio::ip::udp::endpoint const& endpoint);
        void broadcastMessage(network::UDPClientMessage const& message);

    private:
        std::uint8_t _roomNbr;
        std::vector<boost::asio::ip::udp::endpoint> _connectedClientsEndpoints;
        MoveSystem moveSystem;
        DeathSystem deathSystem;
        CollisionSystem collisionSystem;
        DamageSystem damageSystem;
        SpawnSystem spawnSystem;
        std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> _entities;
        SafeQueue<std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>>> &_UDPMessages;
        SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &_UDPMessagesToSend;
    };
}

#endif /* !GAMELOOP_HPP_ */
