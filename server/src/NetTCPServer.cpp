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
    NetTCPServer::NetTCPServer(short port) : _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    {
        acceptConnection();
        _thread = std::thread([this]{ _context.run(); });
    }

    NetTCPServer::~NetTCPServer()
    {
    }

    NetTCPRoom &NetTCPServer::getRoom()
    {
        return _room;
    }

    void NetTCPServer::acceptConnection()
    {
        _acceptor.async_accept(
            [this](boost::system::error_code ec, asio::ip::tcp::socket socket)
            {
                if (!ec) {
                    _room.addClient(socket);
                }
                acceptConnection();
            }
        );
    }

    std::vector<std::unique_ptr<NetTCPServerClient>> &NetTCPServer::getClients()
    {
        return _room.getClients();
    }
}
