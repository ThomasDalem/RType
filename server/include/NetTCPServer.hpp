/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPServer
*/

#ifndef NETTCPSERVER_HPP_
#define NETTCPSERVER_HPP_

#include <boost/asio.hpp>
#include <thread>
#include "NetTCPRoom.hpp"

namespace network
{
    class NetTCPServer
    {
    public:
        NetTCPServer(short port);
        ~NetTCPServer();

        NetTCPRoom &getRoom();
        std::vector<std::unique_ptr<NetTCPServerClient>> &getClients();

    private:
        void acceptConnection();
        void receiveMessage();

    private:
        boost::asio::io_context _context;
        boost::asio::ip::tcp::acceptor _acceptor;
        NetTCPRoom _room;
        std::thread _thread;
    };
}

#endif /* !NETTCPSERVER_HPP_ */
