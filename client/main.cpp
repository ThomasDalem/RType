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

using namespace std;
using namespace client;
void core(vector<string> av) {
    shared_ptr<Client> client = make_shared<Client>();

    client->waitConnection();
    while(!client->getNetworkUDP()->hasMessages());
    network::UDPClientMessage message = *client->getNetworkUDP()->getFirstMessage();
    client->getPlayer(0)->setId(message.uniqueID);
    client->setScoreAndSprite(message);
    if (client->MenusLoop())
        client->game();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
