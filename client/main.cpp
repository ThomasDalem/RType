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
#include "WindowHandler.hpp"

using namespace std;
vector<string> getArgs(char **av) {
    vector<string> args;

    for (size_t i = 0; av && av[i]; i ++)
        args.push_back(string(av[i]));
    return args;
}

bool isDisplayEnv(char **env) {
    vector<string> myEnv = getArgs(env);

    if (myEnv.size() == 0)
        return false;
    for (size_t i = 0; i < myEnv.size(); i ++) {
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    }
    return false;
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