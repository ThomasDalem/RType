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
        try {
            _thread = std::thread([this] {return _context.run();});
        } catch (std::bad_alloc e) {
            _thread.detach();
        }
    }

    NetUDPClient::~NetUDPClient()
    {
        _context.stop();
        _thread.join();
    }

    void NetUDPClient::sendMessage(UDPMessage const& message){
        _socket.send_to(asio::buffer(&message, sizeof(UDPMessage)), *_endpoints.begin());
    }

    void NetUDPClient::receiveMessage() {
        _socket.async_receive_from(asio::buffer(_data, sizeof(UDPClientMessage)), _endpoint,
            std::bind(&NetUDPClient::handleMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetUDPClient::handleMessage(boost::system::error_code const& ec, std::size_t receivedBytes) {
        std::unique_ptr<UDPClientMessage> message = std::make_unique<UDPClientMessage>();

        if (!ec && receivedBytes == sizeof(UDPClientMessage)) {
            std::memcpy(message.get(), _data, sizeof(UDPClientMessage));
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

    std::unique_ptr<UDPClientMessage> NetUDPClient::getFirstMessage()
    {
        std::unique_ptr<UDPClientMessage> messageSave = std::move(_messages.front());
        _messages.pop();
        return std::move(messageSave);
    }
}
