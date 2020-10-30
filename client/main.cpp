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
#include "ErrorHandler.hpp"
#include "WindowHandler.hpp"

using namespace std;
vector<string> getArgs(char **av) {
    vector<string> args;

    for (size_t i = 0; av && av[i]; i ++)
        args.push_back(string(av[i]));
    return args;
}

int main(int ac, char **av, char **env) {
    vector<string> args = getArgs(av);
    WindowHandler windowhdl(1200, 600, "R-Type");

    windowhdl.setFramerate(50);
    while (windowhdl.isOpen()) {
        windowhdl.display();
    }
    windowhdl.~WindowHandler();
    return 0;
}