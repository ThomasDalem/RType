/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#include "Room.hpp"
#include "Main.hpp"
#include "Client.hpp"
#include "Entities.hpp"

Client::Client() {
    _windowhdl = make_shared<WindowHandler>(1910, 1070, "R-Type");
    _net = make_shared<network::NetUDPClient>("127.0.0.1", "8081");
    _score = make_shared<TextSfml>("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);

    // Player in a game
    _players.push_back(make_shared<Player>(0));

    // Window class stats
    _windowhdl->setFramerate(50);
    _windowhdl->addText(_score);
    _windowhdl->addImage(_players[0]->getImage());
    _windowhdl->addText(_players[0]->getNameText());
}
Client::~Client() {
    // for(size_t i = 0; i < _players.size(); i ++)
    //     _players[i]->~Player();
    // _players.~vector();
    // _windowhdl->~WindowHandler();
}

// value[0] : 1 = message à afficher, 0 = le joueur est mort
// value[1] : position x du sprite
// value[2] : position y du sprite
// value[3] : rotation (jsp à quoi ça sert mais Thomas l'a mis donc ça doit servir)
// value[4] : les positions x dans le sprite cheet
// value[5] : les positions y dans le sprite cheet
// value[6] : Longueur dans le sprite cheet
// value[7] : largeur dans le sprite sheet

void Client::game(void) {
    while (_windowhdl->isOpen()) {
        if (_net->hasMessages()) {
            while (_net->hasMessages()) {
                //std::cout << "received a message" << std::endl;
                bool find = false;
                unique_ptr<network::UDPClientMessage> message = _net->getFirstMessage();
                // Check if i know this entity
                if (message->event == network::SendEvent::REMOVE) {
                    for (size_t i = 0; i < _entities.size(); i ++) {
                        if (message->uniqueID == _entities[i]->getId()) {
                            std::cout << message->entitieType << std::endl;
                            _entities.erase(_entities.begin() + i);
                        }
                    }
                }
                if (message->value[0] != 0) {
                    for (size_t i = 0; i < _entities.size(); i ++) {
                        if (message->uniqueID == _entities[i]->getId()) {
                            _entities[i]->getImage()->setRectangleSheep(sf::IntRect(message->value[4], message->value[5], message->value[6], message->value[7]));
                            _entities[i]->getImage()->setPosition(sf::Vector2f(message->value[1], message->value[2]));
                            _entities[i]->getImage()->setScale(sf::Vector2f(3, 3));
                            find = true;
                        }
                    }
                    if (!find) {
                        std::cout << "create new entitie" << std::endl;
                        shared_ptr<Entities> newone = make_shared<Entities>(message->uniqueID, message->entitieType);
                        newone->getImage()->setRectangleSheep(sf::IntRect(message->value[4], message->value[5], message->value[6], message->value[7]));
                        newone->getImage()->setPosition(sf::Vector2f(message->value[1], message->value[2]));
                        _entities.push_back(newone);
                    }
                }
                formatInput(0);
                _windowhdl->getWindow()->clear();
                _windowhdl->dispBackground();
                for (size_t i = 0; i < _entities.size(); i ++)
                    _windowhdl->getWindow()->draw(*_entities[i]->getImage()->getSprite());
                _windowhdl->display();
                    // Draw des entities
            }
        }
        else {
            formatInput(0);
            _windowhdl->getWindow()->clear();
            _windowhdl->dispBackground();
            for (size_t i = 0; i < _entities.size(); i ++) {
                _windowhdl->getWindow()->draw(*_entities[i]->getImage()->getSprite());
            }
            _windowhdl->display();
        }
    }
}

void Client::formatInput(size_t row) {
    network::UDPMessage lastinput;

    switch(_windowhdl->isEvent(*_players[row])) {
        case Input::Left: lastinput = {_players[0]->getId(), {-1, 0}, network::Event::MOVE}; _net->sendMessage(lastinput); break;
        case Input::Right: lastinput = {_players[0]->getId(), {1, 0}, network::Event::MOVE}; _net->sendMessage(lastinput); break;
        case Input::Up: lastinput = {_players[0]->getId(), {0, -1}, network::Event::MOVE}; _net->sendMessage(lastinput); break;
        case Input::Down: lastinput = {_players[0]->getId(), {0, 1}, network::Event::MOVE}; _net->sendMessage(lastinput); break;
        case Input::Shoot: lastinput = {_players[0]->getId(), {}, network::Event::SHOOT}; _net->sendMessage(lastinput); break;
        case Input::Escape: _windowhdl->~WindowHandler(); break;
        default: break;
    }
}

void Client::MenusLoop(void) {
    switch (Mainmenu().loop(_windowhdl->getWindow(), *_players[0])) {
        case Creating: RoomMenu().creatingGame(_windowhdl->getWindow(), *_players[0]); break;
        case Room: RoomMenu().loop(_windowhdl->getWindow(), *_players[0]); break;
        default: break;
    }
    return;
}
shared_ptr<network::NetUDPClient> Client::getNetwork(void) const {return _net;}
shared_ptr<WindowHandler> Client::getWindowHandler(void) const {return _windowhdl;}
shared_ptr<Player> Client::getPlayer(size_t row) const {return row > 4 ? nullptr : _players[row];}
