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
#include "NetCommon.hpp"
#include "ErrorHandler.hpp"
#include "NetUDPClient.hpp"
#include "WindowHandler.hpp"

using namespace std;
vector<string> getArgs(char **av) {
    vector<string> args;

    for (size_t i = 0; av && av[i]; i ++)
        args.push_back(string(av[i]));
    return args;
}

void core(vector<string> av) {
    Player player;
    WindowHandler windowhdl(1910, 1070, "R-Type");
    network::NetUDPClient net("127.0.0.1", "200");
    network::UDPMessage msg = {13, 84, network::Event::ADD};
    shared_ptr<TextSfml> Score = make_shared<TextSfml>("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);

    net.sendMessage(msg);

    windowhdl.setFramerate(50);
    windowhdl.addText(Score);
    switch (Mainmenu().loop(windowhdl.getWindow(), player)) {
        case Creating: RoomMenu().creatingGame(windowhdl.getWindow(), player); break;
        case Room: RoomMenu().loop(windowhdl.getWindow(), player); break;
        default: break;
    }
    windowhdl.addImage(player.getImage());
    windowhdl.addText(player.getNameText());
    while (windowhdl.isOpen()) {
        while (net.hasMessages()) {
            unique_ptr<network::UDPMessage> message = net.getFirstMessage();

            cout << "MESSAGES: " <<  int(message->event) << ", " << message->playerID << ", " << message->value << endl;
        }
        windowhdl.isEvent(player);
        windowhdl.display();
    }
    windowhdl.~WindowHandler();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}