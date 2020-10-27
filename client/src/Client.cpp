/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(string name) {
    this->_name = name;
}
Client::~Client() {}

bool Client::operator=(Client another) {
    this->_name = another.getName();
}

bool Client::operator==(Client another) {
    if (this->_name != another.getName())
        return false;
    return true;
}

string Client::getName(void) const {return _name;}
void Client::setName(string str) {this->_name = str;}
