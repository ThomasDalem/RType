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
#include "ErrorHandler.hpp"
#include "NetUDPClient.hpp"
#include "WindowHandler.hpp"

using namespace std;
void core(vector<string> av) {
    Client client;
    network::UDPMessage msg = {-1, {84}, network::Event::ADD};

    // Wait ID from Server
    client.getNetwork()->sendMessage(msg);
    while(client.getNetwork()->hasMessages()) {
        network::UDPClientMessage message = *client.getNetwork()->getFirstMessage();
        client.getPlayer(0)->setId(message.uniqueID);
    }
    // Menus
    client.MenusLoop();

    // Game
    client.game();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
