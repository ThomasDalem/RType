/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>

using namespace std;
class Client {
    public:
        Client(string name);
        ~Client();

        bool operator=(Client another);
        bool operator==(Client another);

        void setName(string str);
        string getName(void) const;

    private:
        string _name;

    protected:
};

#endif
