/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetTCPClient
*/

#ifndef __NetTCPClient__
#define __NetTCPClient__

#include <queue>
#include <memory>
#include <boost/asio.hpp>

#include "NetCommon.hpp"

using namespace std;
namespace network {
    class NetTCPClient {
        public:
            NetTCPClient(string const &ip, string const &port);
            ~NetTCPClient();

            bool isConnected(void) const;
            bool hasMessages(void) const;
            void sendMessage(TCPMessage const &message);
            unique_ptr<TCPMessage> getFirstMessage(void);

        private:
            void connect(void);
            void receiveMessage(void);
            void handleMessage(boost::system::error_code ec, size_t receivedBytes);

        private:
            thread _thread;
            bool _isConnected;
            char _data[MAX_MESSAGE_LENGTH];
            boost::asio::io_context _context;
            boost::asio::ip::tcp::socket _socket;
            queue<unique_ptr<TCPMessage>> _messages;
            boost::asio::ip::tcp::resolver _resolver;
            boost::asio::ip::tcp::resolver::results_type _endpoints;
        };
}

#endif
