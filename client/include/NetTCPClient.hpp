/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPClient
*/

#ifndef NETTCPCLIENT_HPP_
#define NETTCPCLIENT_HPP_

#include <queue>
#include <memory>
#include <boost/asio.hpp>
#include "NetCommon.hpp"

namespace network
{
    class NetTCPClient
    {
    public:
        NetTCPClient(std::string const& ip, std::string const& port);
        ~NetTCPClient();

        bool isConnected() const;
        bool hasMessages() const;
        std::unique_ptr<TCPMessage> getFirstMessage();
        void sendMessage(TCPMessage const& message);

    private:
        void connect();
        void receiveMessage();
        void handleMessage(boost::system::error_code ec, std::size_t receivedBytes);

    private:
        bool _isConnected;
        boost::asio::io_context _context;
        boost::asio::ip::tcp::resolver _resolver;
        boost::asio::ip::tcp::resolver::results_type _endpoints;
        boost::asio::ip::tcp::socket _socket;
        std::thread _thread;
        std::queue<std::unique_ptr<TCPMessage>> _messages;
        char _data[MAX_MESSAGE_LENGTH];
    };
}

#endif /* !NETTCPCLIENT_HPP_ */
