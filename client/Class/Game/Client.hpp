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
#include "NetUDPClient.hpp"
#include "WindowHandler.hpp"

using namespace std;

namespace client {
    class Client {
        public:
            Client();
            ~Client();

            void game(void);
            bool MenusLoop(void);
            void formatInput(size_t);
            void waitConnection(void);
            size_t getNumbersPlayer(void) const;
            MusicSystem getMusicSystem(void) const;
            shared_ptr<Player> getPlayer(size_t) const;
            shared_ptr<WindowHandler> getWindowHandler(void) const;
            shared_ptr<network::NetUDPClient> getNetwork(void) const;

        private:
            bool isDead;
            MusicSystem _musics;
            Animation _animation;
            shared_ptr<TextSfml> _score;
            vector<shared_ptr<Player>> _players;
            shared_ptr<WindowHandler> _windowhdl;
            vector<shared_ptr<Entities>> _entities;
            shared_ptr<network::NetUDPClient> _net;

        protected:
    };
}

#endif