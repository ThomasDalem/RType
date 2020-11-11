/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Error Handler
*/

#include <vector>
#include <iostream>

#include "ErrorHandler.hpp"

using namespace std;
client::ErrorHandler::ErrorHandler() {}
client::ErrorHandler::~ErrorHandler() {}

vector<string> client::ErrorHandler::getArgs(char **av) {
    vector<string> args;

    for (size_t i = 0; av && av[i]; i ++)
        args.push_back(string(av[i]));
    return args;
}

bool client::ErrorHandler::isDisplayEnv(char **env) {
    vector<string> myEnv = getArgs(env);

    if (myEnv.size() == 0)
        return false;
    for (size_t i = 0; i < myEnv.size(); i ++) {
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    }
    return false;
}