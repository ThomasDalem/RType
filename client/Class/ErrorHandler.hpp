/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Error Handler
*/

#ifndef __ErrorHandler__
#define __ErrorHandler__

#include <vector>

using namespace std;
class ErrorHandler {
    public:
        ErrorHandler();
        ~ErrorHandler();

        bool isDisplayEnv(char **env);
        vector<string> getArgs(char **av);

    private:

    protected:
};

#endif