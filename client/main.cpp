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
#include "Main.hpp"
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
    // TextSfml Score("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);
    WindowHandler windowhdl(1200, 600, "R-Type");

    windowhdl.setFramerate(50);
    // windowhdl.addText(Score);
    player.setName(Mainmenu().loop(windowhdl.getWindow()));
    windowhdl.addImage(player.getImage());
    windowhdl.addText(player.getNameText());
    while (windowhdl.isOpen()) {
        windowhdl.getWindow()->draw(*player.getNameText().getData());
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