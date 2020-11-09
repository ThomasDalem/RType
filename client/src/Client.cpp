/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() {
    _windowhdl = make_shared<WindowHandler>(1910, 1070, "R-Type");

    _players.push_back(make_shared<Player>(1));
    _players.push_back(make_shared<Player>(2));
    _players.push_back(make_shared<Player>(3));
    _players.push_back(make_shared<Player>(4));

    _windowhdl->setFramerate(50);
}
Client::~Client() {}

void Client::operator=(Client another) {

}

bool Client::operator==(Client another) {
    return true;
}

void Client::formatInput(size_t row, shared_ptr<network::NetUDPClient> net) {
    network::UDPMessage lastinput;

    switch(_windowhdl->isEvent(*_players[row])) {
        case Input::Left: lastinput = {13, {-1, 0}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Right: lastinput = {13, {1, 0}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Up: lastinput = {13, {0, -1}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Down: lastinput = {13, {0, 1}, network::Event::MOVE}; net->sendMessage(lastinput); break;
        case Input::Shoot: lastinput = {13, {}, network::Event::SHOOT}; net->sendMessage(lastinput); break;
        case Input::Escape: _windowhdl->~WindowHandler(); break;
        default: break;
    }
}

shared_ptr<WindowHandler> Client::getWindowHandler(void) const {return _windowhdl;}
shared_ptr<Player> Client::getPlayer(size_t row) const {return row > 4 ? nullptr : _players[row];}
