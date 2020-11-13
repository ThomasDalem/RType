/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Room
*/

#include "Room.hpp"

Room::Room(int roomNbr, std::string const& roomName, std::queue<std::pair<network::TCPMessage, int>> &TCPMessagesToSend) :
     _TCPMessagesToSend(TCPMessagesToSend), _roomNbr(roomNbr), _roomName(roomName)
{
    _thread = std::thread(&Room::roomLoop, this);
}

Room::~Room()
{
    _UDPmessages.stop();
    _TCPmessages.stop();
    _thread.join();
}

void Room::roomLoop()
{
    while (1) {
        while (_TCPmessages.empty() == false) {
            std::pair<std::unique_ptr<network::TCPMessage>, int> message;

            if (_TCPmessages.tryGetPop(message)) {
                if (message.first->event == network::TCPEvent::START) {
                    std::pair<network::TCPMessage, int> messageToSend(network::TCPMessage{network::TCPEvent::START, ""}, -1);
                    _TCPMessagesToSend.push(messageToSend);
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
    _UDPmessages.push(message);
}

void Room::pushTCPMessage(std::unique_ptr<network::TCPMessage> &message, int clientID)
{
    std::pair<std::unique_ptr<network::TCPMessage>, int> pair(std::move(message), clientID);
    _TCPmessages.push(pair);
}

std::queue<std::pair<network::TCPMessage, int>> &Room::getTCPMessagesToSend()
{
    return _TCPMessagesToSend;
}
