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
#include "IEntities.hpp"
#include "NetTCPServer.hpp"
#include "NetUDPServer.hpp"
#include "SafeQueue.hpp"

class Room {
public:
    Room(int roomNbr, std::string const& roomName, std::queue<std::pair<network::TCPMessage, int>> &TCPMessagesToSend);
    ~Room();

    void roomLoop();
    void startGameLoop();
    void pushTCPMessage(std::unique_ptr<network::TCPMessage> &message, int clientID);
    void pushUDPMessage(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message);
    std::queue<std::pair<network::TCPMessage, int>> &getTCPMessagesToSend();

private:
    int _roomNbr;
    std::string _roomName;
    std::vector<std::unique_ptr<game_engine::IEntities>> _entities;
    SafeQueue<std::pair<std::unique_ptr<network::TCPMessage>, int>> _TCPmessages;
    std::queue<std::pair<network::TCPMessage, int>> &_TCPMessagesToSend;
    SafeQueue<std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>>> _UDPmessages;
    std::thread _thread;
};

#endif /* !ROOM_HPP_ */
