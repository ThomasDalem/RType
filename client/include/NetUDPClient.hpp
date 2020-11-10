/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetworkClient
*/

#ifndef NETUDPCLIENT_HPP_
#define NETUDPCLIENT_HPP_

#include <queue>
#include <memory>
#include <thread>
#include "NetCommon.hpp"

namespace network
{
    class NetUDPClient {
        public:
            NetUDPClient(std::string const &ip, std::string const &port);
            ~NetUDPClient();

            bool hasMessages() const;
            void sendMessage(UDPMessage const &message);
            std::unique_ptr<UDPClientMessage> getFirstMessage();

        private:
            void receiveMessage();
            void handleMessage(boost::system::error_code const& ec, std::size_t receivedBytes);

        private:
            std::thread _thread;
            boost::asio::io_context _context;
            boost::asio::ip::udp::socket _socket;
            boost::asio::ip::udp::resolver _resolver;
            boost::asio::ip::udp::resolver::results_type _endpoints;
            boost::asio::ip::udp::endpoint _endpoint;
            char _data[MAX_MESSAGE_LENGTH];
            std::queue<std::unique_ptr<UDPClientMessage>> _messages;
    };
}

#endif /* !NETUDPCLIENT_HPP_ */
