/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <map>
#include <thread>
#include "NetTCPServer.hpp"
#include "NetUDPServer.hpp"
#include "SafeQueue.hpp"
#include "UDPClient.hpp"

class Room {
public:
    Room(int roomNbr, std::string const& roomName, SafeQueue<std::pair<network::TCPMessage, int>> &TCPMessagesToSend,
        SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &UDPMessagesToSend);
    ~Room();

    std::string const& getRoomName() const;
    void roomLoop();
    void startGameLoop();
    void pushTCPMessage(std::unique_ptr<network::TCPMessage> &message, int clientID);
    void pushUDPMessage(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message);
    SafeQueue<std::pair<network::TCPMessage, int>> &getTCPMessagesToSend();
    SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &getUDPMessagesToSend();

private:
    int _clientsIDVal;
    int _roomNbr;
    std::string _roomName;
    SafeQueue<std::pair<std::unique_ptr<network::TCPMessage>, int>> _TCPMessages;
    SafeQueue<std::pair<network::TCPMessage, int>> _TCPMessagesToSend;
    SafeQueue<std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>>> _UDPMessages;
    SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &_UDPMessagesToSend;
    std::thread _thread;
};

#endif /* !ROOM_HPP_ */
