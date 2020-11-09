/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPServerClient
*/

#include <iostream>
#include "NetTCPServerClient.hpp"

namespace network
{
    NetTCPServerClient::NetTCPServerClient(boost::asio::ip::tcp::socket &socket) :
        _socket(std::move(socket)), _isConnected(true)
    {
        receiveMessage();
    }

    NetTCPServerClient::~NetTCPServerClient()
    {
    }

    boost::asio::ip::tcp::socket &NetTCPServerClient::getSocket()
    {
        return _socket;
    }

    void NetTCPServerClient::sendMessage(TCPMessage const& message)
    {
        boost::asio::async_write(_socket, boost::asio::buffer(&message, sizeof(TCPMessage)),
            [this](boost::system::error_code ec, std::size_t size)
            {
                if (ec) {
                    _isConnected = false;
                }
            }
        );
    }

    bool NetTCPServerClient::isConnected() const
    {
        return _isConnected;
    }

    int NetTCPServerClient::getID() const
    {
        return _id;
    }

    bool NetTCPServerClient::hasMessages() const
    {
        return !_messages.empty();
    }

    std::unique_ptr<TCPMessage> NetTCPServerClient::getFirstMessage()
    {
        std::unique_ptr<TCPMessage> messageSave = std::move(_messages.front());
        _messages.pop();
        return std::move(messageSave);
    }

    void NetTCPServerClient::receiveMessage()
    {
        TCPMessage message;

        boost::asio::async_read(_socket, boost::asio::buffer(&_data, sizeof(TCPMessage)),
            std::bind(&NetTCPServerClient::handleMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetTCPServerClient::handleMessage(boost::system::error_code ec, std::size_t receivedBytes)
    {
        if (!ec && receivedBytes == sizeof(TCPMessage)) {
            std::unique_ptr<TCPMessage> message = std::make_unique<TCPMessage>();

            if (!ec && receivedBytes == sizeof(TCPMessage)) {
                std::memcpy(message.get(), _data, sizeof(TCPMessage));
                _messages.push(std::move(message));
                receiveMessage();
            } else {
                receiveMessage();
            }
        }
    }
}
