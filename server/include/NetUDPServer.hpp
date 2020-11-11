/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetUDPServer
*/

#ifndef NETSERVER_HPP_
#define NETSERVER_HPP_

#include <queue>
#include <memory>
#include "NetCommon.hpp"

namespace network
{
    class NetUDPServer
    {
    public:
        NetUDPServer(short port);
        ~NetUDPServer();
        void sendMessage(UDPClientMessage const& message, boost::asio::ip::udp::endpoint const& endpoint);
        void broadcastMessage(UDPClientMessage &message);
        bool hasMessages() const;
        std::unique_ptr<std::pair<UDPMessage, boost::asio::ip::udp::endpoint>> getFirstMessage();
        std::vector<boost::asio::ip::udp::endpoint> getAllClient();
        void killClient(boost::asio::ip::udp::endpoint client);
    private:
        void receiveMessage();
        void handleMessage(boost::system::error_code const &ec, std::size_t receivedBytes);
        bool newClientExist() const;

    private:
        std::thread _thread;
        boost::asio::io_context _context;
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _senderEndpoint;
        char _data[MAX_MESSAGE_LENGTH];
        std::vector<boost::asio::ip::udp::endpoint> _clients;
        std::vector<boost::asio::ip::udp::endpoint> _deadClients;
        std::queue<std::unique_ptr<std::pair<UDPMessage, boost::asio::ip::udp::endpoint>>> _messages;
    };
}

#endif /* !NETUDPSERVER_HPP_ */
