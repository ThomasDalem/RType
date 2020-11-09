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

    network::UDPMessage msg = {1, {84}, network::Event::ADD};
    shared_ptr<TextSfml> Score = make_shared<TextSfml>("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);

    client.getWindowHandler()->addText(Score);
    switch (Mainmenu().loop(client.getWindowHandler()->getWindow(), *client.getPlayer(0))) {
        case Creating: RoomMenu().creatingGame(client.getWindowHandler()->getWindow(), *client.getPlayer(0)); break;
        case Room: RoomMenu().loop(client.getWindowHandler()->getWindow(), *client.getPlayer(0)); break;
        default: break;
    }
    client.getWindowHandler()->addImage(client.getPlayer(0)->getImage());
    client.getWindowHandler()->addText(client.getPlayer(0)->getNameText());

    client.getNetwork()->sendMessage(msg);
    while (client.getWindowHandler()->isOpen()) {
        while (client.getNetwork()->hasMessages()) {
            unique_ptr<network::UDPMessage> message = client.getNetwork()->getFirstMessage();

            cout << "MESSAGES: " << int(message->event) << ", " << message->playerID << ", " << message->value << endl;
        }
        client.formatInput(0);
        client.getWindowHandler()->display();
    }
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
