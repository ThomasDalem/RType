/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetUDPServer
*/

#include <iostream>
#include "NetUDPServer.hpp"

using namespace boost;

namespace network
{
    NetUDPServer::NetUDPServer(short port) :
        _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        receiveMessage();
        _thread = std::thread([this] { return _context.run(); });
    }

    NetUDPServer::~NetUDPServer()
    {
    }

    void NetUDPServer::sendMessage(UDPMessage const& message, asio::ip::udp::endpoint const& endpoint)
    {
        _socket.send_to(asio::buffer(&message, sizeof(UDPMessage)), endpoint);
    }

    void NetUDPServer::broadcastMessage(UDPMessage &message)
    {
        for (auto it = _clients.begin(); it != _clients.end(); it++) {
            sendMessage(message, *it);
        }
    }

    void NetUDPServer::receiveMessage()
    {
        _socket.async_receive_from(asio::buffer(_data, MAX_MESSAGE_LENGTH), _senderEndpoint,
            std::bind(&NetUDPServer::handleMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetUDPServer::handleMessage(boost::system::error_code const &ec, std::size_t receivedBytes)
    {
        std::unique_ptr<UDPMessage> message = std::make_unique<UDPMessage>();

        if (!newClientExist()) {
            _clients.push_back(_senderEndpoint);
        }
        if (!ec && receivedBytes == sizeof(UDPMessage)) {
            std::memcpy(message.get(), _data, sizeof(UDPMessage));
            _messages.push(std::move(message));
        }
        receiveMessage();
    }

    bool NetUDPServer::hasMessages() const
    {
        return !_messages.empty();
    }

    std::unique_ptr<UDPMessage> NetUDPServer::getFirstMessage()
    {
        std::unique_ptr<UDPMessage> messageSave = std::move(_messages.front());
        _messages.pop();
        return std::move(messageSave);
    }


    bool NetUDPServer::newClientExist() const
    {
        for (auto it = _clients.begin(); it != _clients.end(); it++) {
            if (_senderEndpoint == *it) {
                return (true);
            }
        }
        return (false);
    }
}
