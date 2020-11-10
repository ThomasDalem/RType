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
    shared_ptr<Client> client = make_shared<Client>();
    network::UDPMessage msg = {-1, {84}, network::Event::ADD};
    shared_ptr<ImageSFML> waiter = make_shared<ImageSFML>("./resources/sprites/background.png");
    shared_ptr<TextSfml> textw = make_shared<TextSfml>("Wait for Server...", "./resources/fonts/2MASS.otf", sf::Color::White, 950 - 99, 850);

    client->getNetwork()->sendMessage(msg);
    for (int attempt = -3; !client->getNetwork()->hasMessages(); attempt ++) {
        textw->setString("Wait for Server..." + (attempt > 0 ? "(attempt " + to_string(attempt) + ")" : ""));
        client->getWindowHandler()->getWindow()->draw(*waiter->getSprite());
        client->getWindowHandler()->getWindow()->draw(*textw->getData());
        client->getWindowHandler()->display();
        sleep(attempt > 0 ? 5 : 1);
        client->getNetwork()->sendMessage(msg);
    }

    network::UDPClientMessage message = *client->getNetwork()->getFirstMessage();
    client->getNetwork()->sendMessage({-1, {84}, network::Event::CONFIRMCONNECTION});
    client->getPlayer(0)->setId(1);
    //client->MenusLoop();
    client->game();
}

int main(int ac, char **argv, char **env) {
    vector<string> av = ErrorHandler().getArgs(argv);

    if (!ErrorHandler().isDisplayEnv(env))
        return 84;
    cout << "start" << endl;
    core(av);
    return 0;
}
