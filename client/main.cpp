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
void core(vector<string> av) {
    MusicSFML music;
    shared_ptr<client::Client> client = make_shared<client::Client>();

    music.load("./resources/sounds/main.ogg");
    music.start();
    client->waitConnection();
    //client->getNetwork()->sendMessage({-1, {84}, network::Event::CONFIRMCONNECTION});
    while(!client->getNetwork()->hasMessages());
    network::UDPClientMessage message = *client->getNetwork()->getFirstMessage();
    client->getPlayer(0)->setId(message.uniqueID);
    if (client->MenusLoop())
        client->game();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = client::ErrorHandler().getArgs(argv);

    if (!client::ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
