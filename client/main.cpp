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
#include "Player.hpp"
#include "ErrorHandler.hpp"
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
    WindowHandler windowhdl(1200, 600, "R-Type");

    player.setName("JustRoméo");
    windowhdl.setFramerate(50);
    windowhdl.addImage(player.getImage());
    while (windowhdl.isOpen()) {
        windowhdl.isEvent();

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