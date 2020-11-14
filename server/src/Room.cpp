/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Room
*/

#include "GameLoop.hpp"
#include "Room.hpp"

Room::Room(int roomNbr, std::string const& roomName, SafeQueue<std::pair<network::TCPMessage, int>> &TCPMessagesToSend, 
    SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &UDPMessagesToSend) :
    _clientsIDVal(0), _UDPMessagesToSend(UDPMessagesToSend), _roomNbr(roomNbr),
    _roomName(roomName)
{
    _thread = std::thread(&Room::roomLoop, this);
}

Room::~Room()
{
    _UDPMessages.stop();
    _TCPMessages.stop();
    _thread.join();
}

void Room::roomLoop()
{
    while (1) {
        while (_TCPMessages.empty() == false) {
            std::pair<std::unique_ptr<network::TCPMessage>, int> message;
            if (_TCPMessages.tryGetPop(message)) {
                if (message.first->event == network::TCPEvent::START) {
                    std::cout << "Received START signal" << std::endl;
                    std::pair<network::TCPMessage, int> messageToSend(network::TCPMessage{network::TCPEvent::START, ""}, -1);
                    _TCPMessagesToSend.push(messageToSend);
                    game_engine::GameLoop gameLoop(_roomNbr, _UDPMessages, _UDPMessagesToSend);
                    gameLoop.gameLoop();
                } else {
                    std::cout << "NO" << std::endl;
                }
            }
        }
    }
}

void Room::startGameLoop()
{

}

void Room::pushUDPMessage(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message)
{
    _UDPMessages.push(message);
}

void Room::pushTCPMessage(std::unique_ptr<network::TCPMessage> &message, int clientID)
{
    std::pair<std::unique_ptr<network::TCPMessage>, int> pair(std::move(message), clientID);
    _TCPMessages.push(pair);
}

SafeQueue<std::pair<network::TCPMessage, int>> &Room::getTCPMessagesToSend()
{
    return _TCPMessagesToSend;
}

SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> &Room::getUDPMessagesToSend()
{
    return _UDPMessagesToSend;
}
