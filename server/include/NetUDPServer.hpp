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

        void sendMessage(UDPMessage const& message, boost::asio::ip::udp::endpoint const& endpoint);
        void broadcastMessage(UDPMessage &message);
        bool hasMessages() const;
        std::unique_ptr<UDPMessage> getFirstMessage();

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
        std::queue<std::unique_ptr<UDPMessage>> _messages;
    };
}

#endif /* !NETUDPSERVER_HPP_ */
