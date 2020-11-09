/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() {
    _players.push_back(make_shared<Player>(1));
    _players.push_back(make_shared<Player>(2));
    _players.push_back(make_shared<Player>(3));
    _players.push_back(make_shared<Player>(4));
}
Client::~Client() {}

void Client::operator=(Client another) {

}

bool Client::operator==(Client another) {
    return true;
}

void Client::formatInput(size_t row, shared_ptr<network::NetUDPClient> net, shared_ptr<WindowHandler> windowhdl) {
    network::UDPMessage lastinput;

    switch(windowhdl->isEvent(*_players[row])) {
        case Input::Left: lastinput = {13, {-1, 0}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Right: lastinput = {13, {1, 0}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Up: lastinput = {13, {0, -1}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Down: lastinput = {13, {0, 1}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Shoot: lastinput = {13, {}, network::Event::SHOOT}; net->sendMessage(lastinput); break;
        case Input::Escape: windowhdl->~WindowHandler(); break;
        default: break;
    }
}

shared_ptr<Player> Client::getPlayer(size_t row) const {return row > 4 ? nullptr : _players[row];}
