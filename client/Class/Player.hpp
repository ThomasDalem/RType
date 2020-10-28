/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#ifndef __Player__
#define __Player__

#include <iostream>

using namespace std;
class Player {
    public:
        Player();
        ~Player();

        void setName(string str);
        string getName(void) const;

    private:
        string _name;

    protected:
};

#endif
