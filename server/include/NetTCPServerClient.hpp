/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPServerClient
*/

#ifndef NETTCPSERVERCLIENT_HPP_
#define NETTCPSERVERCLIENT_HPP_

#include <queue>
#include <memory>

#include "NetCommon.hpp"

namespace network
{
    class NetTCPServerClient
    {
    public:
        NetTCPServerClient(boost::asio::ip::tcp::socket &socket, int id);
        ~NetTCPServerClient();

        boost::asio::ip::tcp::socket &getSocket();
        int getRoomID() const;
        int getID() const;
        void setRoomID(int id);
        void sendMessage(TCPMessage const& message);
        bool isConnected() const;
        bool hasMessages() const;
        std::unique_ptr<TCPMessage> getFirstMessage();

    private:
        void receiveMessage();
        void handleMessage(boost::system::error_code ec, std::size_t receivedBytes);

    private:
        int _roomID;
        int _id;
        bool _isConnected;
        boost::asio::ip::tcp::socket _socket;
        std::queue<std::unique_ptr<TCPMessage>> _messages;
        char _data[MAX_MESSAGE_LENGTH];
    };
}

#endif /* !NETTCPSERVERCLIENT_HPP_ */
