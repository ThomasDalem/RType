/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** NetUDPClient
*/

#include <iostream>
#include "NetUDPClient.hpp"

using namespace boost;

namespace network
{
    NetUDPClient::NetUDPClient(std::string const &ip, std::string const &port) :
        _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)), _resolver(_context),
        _endpoints(_resolver.resolve(asio::ip::udp::v4(), ip, port))
    {
        receiveMessage();
        _thread = std::thread([this] { return _context.run(); });
    }

    NetUDPClient::~NetUDPClient()
    {
    }

    void NetUDPClient::sendMessage(UDPMessage const& message)
    {
        _socket.send_to(asio::buffer(&message, sizeof(UDPMessage)), *_endpoints.begin());
    }

    void NetUDPClient::receiveMessage()
    {
        _socket.async_receive_from(asio::buffer(_data, MAX_MESSAGE_LENGTH), _endpoint,
            std::bind(&NetUDPClient::handleMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetUDPClient::handleMessage(boost::system::error_code const& ec, std::size_t receivedBytes)
    {
        std::unique_ptr<UDPMessage> message = std::make_unique<UDPMessage>();

        if (!ec && receivedBytes == sizeof(UDPMessage)) {
            std::memcpy(message.get(), _data, sizeof(UDPMessage));
            _messages.push(std::move(message));
            receiveMessage();
        } else {
            receiveMessage();
        }
    }

    bool NetUDPClient::hasMessages() const
    {
        return !_messages.empty();
    }

    std::unique_ptr<UDPMessage> NetUDPClient::getFirstMessage()
    {
        std::unique_ptr<UDPMessage> messageSave = std::move(_messages.front());
        _messages.pop();
        return std::move(messageSave);
    }
}
