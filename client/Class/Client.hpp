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
        void formatInput(size_t, shared_ptr<network::NetUDPClient>, shared_ptr<WindowHandler>);

    private:
        vector<shared_ptr<Player>> _players;

    protected:
};

#endif
