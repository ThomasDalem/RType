/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** main
*/

#include <vector>
#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "Room.hpp"
#include "Main.hpp"
#include "Player.hpp"
#include "Client.hpp"
#include "NetCommon.hpp"
#include "MusicSFML.hpp"
#include "ErrorHandler.hpp"
#include "NetUDPClient.hpp"
#include "WindowHandler.hpp"
#include "NetTCPClient.hpp"

using namespace std;
using namespace client;
void core(vector<string> av) {
    Client client(av[1], av[2], av[3]);
    // network::TCPMessage message1 = {network::TCPEvent::CREATE_ROOM, {-1}};

    // while (!TCPClient.isConnected());
    // TCPClient.sendMessage(message1);
    // TCPClient.sendMessage(network::TCPMessage{network::TCPEvent::CONNECT, {char(roomNbr), 0}});
    // while (1) {
    //     if (TCPClient.hasMessages()) {
    //         std::unique_ptr<network::TCPMessage> receivedMessage = TCPClient.getFirstMessage();
    //         if (receivedMessage->event == network::TCPEvent::CONNECT) {
    //             std::cout << "Connected to room" << int(roomNbr) << std::endl;
    //             std::cout << "Sending start signal..." << std::endl;
    //             network::TCPMessage msg = {network::TCPMessage{network::TCPEvent::START, {char(roomNbr), 0}}};
    //             TCPClient.sendMessage(msg);
    //         } else if (receivedMessage->event == network::TCPEvent::START) {
    //             std::cout << "Game is starting..." << std::endl;
    //             break;
    //         }
    //     }
    // }

    // cout << "TCP: ...";
    while (!client.isTCPConnected());
    // cout << "Connected !" << endl;
    // if (!client.getWindowHandler()->isOpen())
    //     return;
    // Menus
    // client.waitConnection();
    if (client.MenusLoop())
        client.game();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
