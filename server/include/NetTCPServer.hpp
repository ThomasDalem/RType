/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPServer
*/

#ifndef NETTCPSERVER_HPP_
#define NETTCPSERVER_HPP_

#include <thread>
#include <boost/asio.hpp>
#include <vector>
#include <list>
#include "NetTCPServerClient.hpp"

namespace network
{
    class NetTCPServer
    {
    public:
        NetTCPServer(short port);
        ~NetTCPServer();

        std::list<std::unique_ptr<NetTCPServerClient>> &getClients();

    private:
        void acceptConnection();
        void receiveMessage();

    private:
        boost::asio::io_context _context;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::list<std::unique_ptr<NetTCPServerClient>> _clients;
        std::thread _thread;
        int _clientsIDNbr;
    };
}

#endif /* !NETTCPSERVER_HPP_ */
