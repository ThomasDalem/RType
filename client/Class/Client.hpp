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

        void operator=(Client another);
        bool operator==(Client another);

        shared_ptr<Player> getPlayer(size_t) const;
        shared_ptr<WindowHandler> getWindowHandler(void) const;
        void formatInput(size_t, shared_ptr<network::NetUDPClient>);

    private:
        vector<shared_ptr<Player>> _players;
        shared_ptr<WindowHandler> _windowhdl;

    protected:
};

#endif
