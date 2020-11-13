/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Server
*/

#include <list>
#include "Server.hpp"

Server::Server(short tcpServerPort, short udpServerPort) : _TCPServer(tcpServerPort), _UDPServer(udpServerPort), _roomsCounter(0)
{
}

Server::~Server()
{
}

void Server::mainLoop()
{
    std::list<std::unique_ptr<network::NetTCPServerClient>> &clients = _TCPServer.getClients();

    while (1) {
        for (auto it = _TCPServer.getClients().begin(); it != _TCPServer.getClients().end(); it++) {
            handleTCPMessages(it->get());
        }
        sendTCPMessagesFromRooms();
        //while (_UDPServer.hasMessages()) {
        //    std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> message = _UDPServer.getFirstMessage();
        //}
    }
}

void Server::handleTCPMessages(network::NetTCPServerClient *client)
{
    while (client->hasMessages()) {
        std::unique_ptr<network::TCPMessage> message = client->getFirstMessage();
        switch (message->event)
        {
        case network::TCPEvent::CREATE_ROOM:
            createRoom(client, message);
            break;
        case network::TCPEvent::CONNECT:
            connectClientToRoom(client, message->data[0], &message->data[1]);
            break;
        case network::TCPEvent::DISCONNECT:
            disconnectClientFromRoom(client, message);
            break;
        case network::TCPEvent::GET_ROOMS:
            sendRoomsToClient(client);
        default:
            break;
        }
    }
}

void Server::broadcastTCPMessageToRoom(network::TCPMessage const& message, int roomNbr)
{
    for (auto it = _TCPServer.getClients().begin(); it != _TCPServer.getClients().end(); it++) {
        if (it->get()->getRoomID() == roomNbr) {
            it->get()->sendMessage(message);
        }
    }
}

void Server::createRoom(network::NetTCPServerClient *client, std::unique_ptr<network::TCPMessage> const& message)
{
    if (client->getRoomID() != -1) {
        client->sendMessage(network::TCPMessage{network::TCPEvent::ERROR});
        return;
    }
    _rooms[_roomsCounter] = std::make_unique<Room>(_roomsCounter, message->data, _TCPMessageToSend);
    client->sendMessage(network::TCPMessage{network::TCPEvent::CREATE_ROOM, {char(_roomsCounter), '\0'}});
    _roomsCounter++;
}

void Server::connectClientToRoom(network::NetTCPServerClient *client, int roomNbr, char *data)
{
    if (client->getRoomID() != -1) {
        client->sendMessage(network::TCPMessage{network::TCPEvent::ERROR});
    }
    auto it = _rooms.find(roomNbr);
    network::TCPMessage message = {network::TCPEvent::ERROR};

    if (it == _rooms.end()) {
        client->sendMessage(message);
        return;
    }
    message.event = network::TCPEvent::CONNECT;
    std::memcpy(&message.data, data, 1023);
    client->setRoomID(roomNbr);
    broadcastTCPMessageToRoom(message, roomNbr);
}

void Server::disconnectClientFromRoom(network::NetTCPServerClient *client, std::unique_ptr<network::TCPMessage> &message)
{
    if (client->getRoomID() == -1) {
        client->sendMessage(network::TCPMessage{network::TCPEvent::ERROR});
        return;
    }
    client->setRoomID(-1);
    _rooms[client->getRoomID()]->pushTCPMessage(message, client->getID());
}

void Server::sendTCPMessagesFromRooms()
{
    for (auto it = _rooms.begin(); it != _rooms.end(); it++) {
        while (it->second->getTCPMessagesToSend().size() > 0) {
            std::cout << it->second->getTCPMessagesToSend().size() << " messages left" << std::endl;
            std::pair<network::TCPMessage, int> message = it->second->getTCPMessagesToSend().front();
            if (message.second == -1) {
                broadcastTCPMessageToRoom(message.first, it->first);
            } else {
                sendMessageToClient(message.first, message.second);
            }
            it->second->getTCPMessagesToSend().pop();
        }
    }
}

void Server::sendRoomsToClient(network::NetTCPServerClient *client)
{
    char _roomsNbr[_rooms.size() + 1];
    int i = 0;

    for (auto it = _rooms.begin(); it != _rooms.end(); it++) {
        _roomsNbr[i] = it->first;
        i++;
    }
    _roomsNbr[_rooms.size()] = '\0';
    network::TCPMessage message = {network::TCPEvent::GET_ROOMS};
    message.data[0] = _rooms.size();
    std::memcpy(&message.data[1], _roomsNbr, _rooms.size());
    client->sendMessage(message);
}

void Server::sendMessageToClient(network::TCPMessage const& message, int clientNbr)
{
    for (auto it = _TCPServer.getClients().begin(); it != _TCPServer.getClients().end(); it++) {
        if (it->get()->getID() == clientNbr) {
            it->get()->sendMessage(message);
        }
    }
}
