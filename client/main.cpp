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

    client.waitConnection();
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
