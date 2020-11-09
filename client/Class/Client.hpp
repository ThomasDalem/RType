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
#include "NetUDPClient.hpp"
#include "WindowHandler.hpp"

using namespace std;
class Client {
    public:
        Client();
        ~Client();

        void game(void);
        void formatInput(size_t);
        shared_ptr<Player> getPlayer(size_t) const;
        shared_ptr<WindowHandler> getWindowHandler(void) const;
        shared_ptr<network::NetUDPClient> getNetwork(void) const;

    private:
        vector<shared_ptr<Player>> _players;
        shared_ptr<WindowHandler> _windowhdl;
        shared_ptr<network::NetUDPClient> _net;

    protected:
};

#endif
