/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#ifndef __Client__
#define __Client__

#include <vector>
#include <memory>
#include <iostream>

#include "Player.hpp"
#include "Entities.hpp"
#include "Animation.hpp"
#include "MusicSystem.hpp"
#include "Environment.hpp"
#include "NetUDPClient.hpp"
#include "NetTCPClient.hpp"
#include "WindowHandler.hpp"

using namespace std;

namespace client {
    class Client {
        public:
            Client(string const& ip, string const& tcpPort, string const& udpPort);
            ~Client();

            void game(void);
            bool MenusLoop(void);
            void formatInput(size_t);
            void waitConnection(void);
            bool isTCPConnected(void);
            void sendDisconnection(void);
            size_t getNumbersPlayer(void) const;
            MusicSystem getMusicSystem(void) const;
            shared_ptr<Player> getPlayer(size_t) const;
            void death(network::UDPClientMessage message);
            void create(network::UDPClientMessage message);
            void remove(network::UDPClientMessage message);
            bool update(network::UDPClientMessage message);
            void disconnection(network::UDPClientMessage message);
            shared_ptr<WindowHandler> getWindowHandler(void) const;
            void setScoreAndSprite(network::UDPClientMessage message);
            network::NetUDPClient &getNetworkUDP(void);
            network::NetUDPClient &getNetworkUDPTCP(void);
            void setRoomNbr(int nbr);

        private:
            bool isDead;
            MusicSystem _musics;
            Animation _animation;
            shared_ptr<TextSfml> _score;
            vector<shared_ptr<Player>> _players;
            shared_ptr<WindowHandler> _windowhdl;
            shared_ptr<Environment> _environment;
            vector<shared_ptr<Entities>> _entities;
            network::NetUDPClient _netUDP;
            network::NetTCPClient _netTCP;
            std::uint8_t _roomNbr;

        protected:
    };
}

#endif
