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
<<<<<<< HEAD
    MusicSFML music;
    shared_ptr<Client> client = make_shared<Client>();
=======
    shared_ptr<client::Client> client = make_shared<client::Client>();
>>>>>>> 37db647d159404fdcecca9a2c2c5827e660b1c67

    music.load("./resources/sounds/main.ogg");
    music.start();
    client->waitConnection();
    //client->getNetwork()->sendMessage({-1, {84}, network::Event::CONFIRMCONNECTION});
    while(!client->getNetwork()->hasMessages());
    network::UDPClientMessage message = *client->getNetwork()->getFirstMessage();
    client->getPlayer(0)->setId(message.uniqueID);
<<<<<<< HEAD
    if (client->MenusLoop())
        client->game();
=======
    //if (client->MenusLoop())
    // cout << "Client Id: " << to_string(client->getPlayer(0)->getId()) << endl;
    client->game();
>>>>>>> 37db647d159404fdcecca9a2c2c5827e660b1c67
}

int main(int ac, char **argv, char **env) {
    vector<string> av = client::ErrorHandler().getArgs(argv);

    if (!client::ErrorHandler().isDisplayEnv(env))
        return 84;
    core(av);
    return 0;
}
