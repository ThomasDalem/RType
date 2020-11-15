/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPServer
*/

#include <iostream>
#include "NetTCPServer.hpp"
#include "NetTCPServerClient.hpp"

using namespace boost;

namespace network
{
    NetTCPServer::NetTCPServer(short port) :
        _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _clientsIDNbr(0)
    {
        std::cout << "ok" << std::endl;
        acceptConnection();
        _thread = std::thread([this]{ _context.run(); });
    }

    NetTCPServer::~NetTCPServer()
    {
        _context.stop();
        _thread.join();
    }

    void NetTCPServer::acceptConnection()
    {
        _acceptor.async_accept(
            [this](boost::system::error_code ec, asio::ip::tcp::socket socket)
            {
                if (!ec) {
                    _clients.push_back(std::make_unique<NetTCPServerClient>(socket, _clientsIDNbr));
                    _clientsIDNbr++;
                }
                acceptConnection();
            }
        );
    }

    std::list<std::unique_ptr<NetTCPServerClient>> &NetTCPServer::getClients()
    {
        return _clients;
    }
}
