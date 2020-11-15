/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <queue>
#include <memory>
#include <unordered_map>
#include "Room.hpp"
#include "NetTCPServer.hpp"
#include "NetUDPServer.hpp"

class Server {
public:
    Server(short tcpServerPort, short udpServerPort);
    ~Server();

    void mainLoop();

private:
    void handleUDPMessages(std::unique_ptr<std::pair<network::UDPMessage, boost::asio::ip::udp::endpoint>> &message);
    void handleTCPMessages(network::NetTCPServerClient *client);
    void broadcastTCPMessageToRoom(network::TCPMessage const& message, int roomNbr);
    void createRoom(network::NetTCPServerClient *client, std::unique_ptr<network::TCPMessage> const& message);
    void connectClientToRoom(network::NetTCPServerClient *client, int roomNbr, char *data);
    void disconnectClientFromRoom(network::NetTCPServerClient *client, std::unique_ptr<network::TCPMessage> &message);
    void sendRoomInfo(network::NetTCPServerClient *client, std::unique_ptr<network::TCPMessage> &message);
    void sendTCPMessagesFromRooms();
    void sendUDPMessagesFromRooms();
    void sendRoomsToClient(network::NetTCPServerClient *clientNbr);
    void sendTCPMessageToClient(network::TCPMessage const& message, int clientNbr);

private:
    network::NetTCPServer _TCPServer;
    network::NetUDPServer _UDPServer;
    std::unordered_map<int, std::unique_ptr<Room>> _rooms;
    SafeQueue<std::pair<network::TCPMessage, int>> _TCPMessagesToSend;
    SafeQueue<std::unique_ptr<std::pair<network::UDPClientMessage, boost::asio::ip::udp::endpoint>>> _UDPMessagesToSend;
    int _roomsCounter;
};

#endif /* !SERVER_HPP_ */
