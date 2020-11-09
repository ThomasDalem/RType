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
    shared_ptr<WindowHandler> windowhdl = make_shared<WindowHandler>(1910, 1070, "R-Type");
    shared_ptr<network::NetUDPClient> net = make_shared<network::NetUDPClient>("127.0.0.1", "8081");
    shared_ptr<TextSfml> Score = make_shared<TextSfml>("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);

    windowhdl->setFramerate(50);
    windowhdl->addText(Score);
    switch (Mainmenu().loop(windowhdl->getWindow(), *client.getPlayer(0))) {
        case Creating: RoomMenu().creatingGame(windowhdl->getWindow(), *client.getPlayer(0)); break;
        case Room: RoomMenu().loop(windowhdl->getWindow(), *client.getPlayer(0)); break;
        default: break;
    }
    windowhdl->addImage(client.getPlayer(0)->getImage());
    windowhdl->addText(client.getPlayer(0)->getNameText());

    net->sendMessage(msg);
    while (windowhdl->isOpen()) {
        while (net->hasMessages()) {
            unique_ptr<network::UDPMessage> message = net->getFirstMessage();

            cout << "MESSAGES: " << int(message->event) << ", " << message->playerID << ", " << message->value << endl;
        }
        client.formatInput(0, net, windowhdl);
        windowhdl->display();
    }
    windowhdl->~WindowHandler();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
