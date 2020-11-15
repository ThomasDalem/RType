/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPRoom
*/

#include <iostream>
#include "NetTCPRoom.hpp"

namespace network
{
    NetTCPRoom::NetTCPRoom()
    {
    }

    NetTCPRoom::~NetTCPRoom()
    {
    }

    void NetTCPRoom::addClient(boost::asio::ip::tcp::socket &socket)
    {
        _clients.push_back(std::make_unique<NetTCPServerClient>(socket));
    }

    void NetTCPRoom::broadcastMessage(TCPMessage const& message)
    {
        for (auto it = _clients.begin(); it != _clients.end(); it++) {
            if (it->get()->isConnected()) {
                it->get()->sendMessage(message);
            }
        }
    }

    std::vector<std::unique_ptr<NetTCPServerClient>> &NetTCPRoom::getClients()
    {
        return _clients;
    }
}
