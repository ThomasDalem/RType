/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPRoom
*/

#ifndef NETTCPROOM_HPP_
#define NETTCPROOM_HPP_

#include <vector>
#include <memory>
#include "NetTCPServerClient.hpp"

namespace network
{
    class NetTCPRoom
    {
    public:
        NetTCPRoom();
        ~NetTCPRoom();

        void addClient(boost::asio::ip::tcp::socket &socket);
        void broadcastMessage(TCPMessage const& message);
        std::vector<std::unique_ptr<NetTCPServerClient>> &getClients();

    private:
        std::vector<std::unique_ptr<NetTCPServerClient>> _clients;
    };
}

#endif /* !NETTCPROOM_HPP_ */
