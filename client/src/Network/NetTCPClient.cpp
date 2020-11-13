/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPClient
*/

#include <thread>
#include <iostream>
#include "NetTCPClient.hpp"

namespace network
{
    NetTCPClient::NetTCPClient(std::string const& ip, std::string const& port) :
        _resolver(_context), _endpoints(_resolver.resolve(ip, port)), _socket(_context)
    {
        connect();
        _thread = std::thread([this]{ _context.run(); });
    }

    NetTCPClient::~NetTCPClient()
    {
    }

    bool NetTCPClient::isConnected() const
    {
        return _isConnected;
    }

    bool NetTCPClient::hasMessages() const
    {
        return !_messages.empty();
    }

    std::unique_ptr<TCPMessage> NetTCPClient::getFirstMessage()
    {
        std::unique_ptr<TCPMessage> messageSave = std::move(_messages.front());
        _messages.pop();
        return std::move(messageSave);
    }

    void NetTCPClient::sendMessage(TCPMessage const& message)
    {
        std::cout << "Message: " << int(message.event) << std::endl;
        boost::asio::async_write(_socket, boost::asio::buffer(&message, sizeof(TCPMessage)),
            [this](boost::system::error_code ec, std::size_t size)
            {
                if (ec) {
                    _isConnected = false;
                }
            }
        );
    }

    void NetTCPClient::connect()
    {
        boost::asio::async_connect(_socket, _endpoints,
            [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint ep)
            {
                if (!ec) {
                    _isConnected = true;
                    receiveMessage();
                } else {
                    std::cerr << "Could not connect to server" << std::endl;
                }
            }
        );
    }

    void NetTCPClient::receiveMessage()
    {
        TCPMessage message;

        boost::asio::async_read(_socket, boost::asio::buffer(&_data, sizeof(TCPMessage)),
            std::bind(&NetTCPClient::handleMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetTCPClient::handleMessage(boost::system::error_code ec, std::size_t receivedBytes)
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
