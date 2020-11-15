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

using namespace client;
Client::Client(string const& ip, string const& tcpPort, string const& udpPort) : _netUDP(ip, udpPort), _netTCP(ip, tcpPort) {
    //Data settings
    isDead = false;
    _animation = Animation();
    _players.push_back(make_shared<Player>(0));
    _environment = make_shared<Environment>();
    _windowhdl = make_shared<WindowHandler>(1910, 1070, "R-Type");
    _score = make_shared<TextSfml>("Score: ", "./resources/fonts/2MASS.otf", sf::Color::White, 25, 25);

    //Windows Settings
    _windowhdl->setFramerate(60);
    //_windowhdl->addText(_score);
    _windowhdl->addImage(_players[0]->getImage());
    //_windowhdl->addText(_players[0]->getNameText());

    //TCP Connection
    //network::TCPMessage msg = {network::TCPEvent::CONNECT, 0};
    //_netTCP->sendMessage(msg);
}

Client::~Client() {
    sendDisconnection();
    _entities.clear();
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
    _netUDP.sendMessage({-1, {84}, network::Event::CONFIRMCONNECTION, _roomNbr});
    while(!_netUDP.hasMessages());
    unique_ptr<network::UDPClientMessage> message = _netUDP.getFirstMessage();
    getPlayer(0)->setId(message->uniqueID);
    setScoreAndSprite(*message);
    while (_windowhdl->isOpen()) {
        while (_netUDP.hasMessages()) {
            unique_ptr<network::UDPClientMessage> message = _netUDP.getFirstMessage();
            if (message->event == network::SendEvent::DEAD)
                return;
            death(*message);
            remove(*message);
            if (message->value[0] != 0)
                if (!update(*message))
                    create(*message);
        }
        formatInput(0);
        _windowhdl->dispBackground();
        if (_animation.checkTimerAnimation())
            _animation.updateAnimation(_entities);
        _windowhdl->dispEntities(_entities);
        _windowhdl->dispEnvironment(_environment);
        _windowhdl->display();
    }
}

void Client::sendDisconnection()
{
    _netUDP.sendMessage({_players[0]->getId(), {-1, 0}, network::Event::DISCONNECTION});
}

void Client::death(network::UDPClientMessage message) {
    if (message.event == network::SendEvent::DEAD)
        isDead = true;
}

void Client::disconnection(network::UDPClientMessage message) {
    if (message.event == network::SendEvent::DESCONNECTCLIENT)
        return;
}

void Client::remove(network::UDPClientMessage message) {
    if (message.event == network::SendEvent::REMOVE)
        for (size_t i = 0; i < _entities.size(); i ++)
            if (message.uniqueID == _entities[i]->getId())
                _entities.erase(_entities.begin() + i);
}

bool Client::update(network::UDPClientMessage message) {
    if (message.entitieType == 2) {
        _environment->setHealh(message.value[1]);
        _environment->setScore(message.value[2]);
        return true;
    }
    for (size_t i = 0; i < _entities.size(); i ++) {
        if (message.uniqueID == _entities[i]->getId()) {
            _entities[i]->getImage()->setPosition(sf::Vector2f(message.value[1], message.value[2]));
            _entities[i]->getImage()->setScale(sf::Vector2f(3, 3));
            return true;
        }
    }
    return false;
}

void Client::setScoreAndSprite(network::UDPClientMessage message) {
    _environment->setPlayerRectangle(sf::IntRect(message.value[4], message.value[5], message.value[6], message.value[7]));
}

void Client::create(network::UDPClientMessage message) {
    shared_ptr<Entities> newone = make_shared<Entities>(message.uniqueID, message.entitieType);

    if (message.entitieType == 1)
        _musics.shot();
    newone->getImage()->setRectangleSheep(sf::IntRect(message.value[4], message.value[5], message.value[6], message.value[7]));
    newone->getImage()->setPosition(sf::Vector2f(message.value[1], message.value[2]));
    _entities.push_back(newone);
}

void Client::formatInput(size_t row) {
    network::UDPMessage lastinput;

    if (isDead) {
        if (_windowhdl->isEvent(*_players[row]) == Input::Escape)
            _windowhdl->close();
        return;
    } switch(_windowhdl->isEvent(*_players[row])) {
        case Input::Left: lastinput = {_players[0]->getId(), {-1, 0}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::Right: lastinput = {_players[0]->getId(), {1, 0}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::Up: lastinput = {_players[0]->getId(), {0, -1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::Down: lastinput = {_players[0]->getId(), {0, 1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::LeftUp: lastinput = {_players[0]->getId(), {-1, -1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::RightUp: lastinput = {_players[0]->getId(), {1, -1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::LeftDown: lastinput = {_players[0]->getId(), {-1, 1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::RightDown: lastinput = {_players[0]->getId(), {1, 1}, network::Event::MOVE, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::Shoot: lastinput = {_players[0]->getId(), {}, network::Event::SHOOT, _roomNbr}; _netUDP.sendMessage(lastinput); break;
        case Input::Escape: _windowhdl->close();
        default: break;
    }
}

bool Client::MenusLoop(void) {
    int roomNbr = -1;
    bool rooms = true;
    bool isLooping = true;
    network::TCPMessage message = {network::TCPEvent::GET_ROOMS, {-1}};

    _netTCP.sendMessage(message);
    while (rooms) {
        if (_netTCP.hasMessages()) {
            unique_ptr<network::TCPMessage> resp = _netTCP.getFirstMessage();
            if (resp->event == network::TCPEvent::GET_ROOMS) {
                roomNbr = resp->data[0];
                rooms = false;
            }
        }
    } while (isLooping) {
        ReturnMain mainissue = Mainmenu().loop(_windowhdl->getWindow(), *_players[0]);

        if (mainissue == Creating) {
            ReturnRoom roomissue = RoomMenu().creatingGame(_windowhdl->getWindow(), _players, _netTCP, roomNbr);

            switch(roomissue) {
                case ReturnRoom::Continue: isLooping = false; break;
                case ReturnRoom::Back: break;
                case ReturnRoom::Salle: cout << "Entering in the room" << endl; break;
            }
        } else if (mainissue == Room) {
            ReturnRoom roomissue = RoomMenu("wsh", roomNbr).loop(_windowhdl->getWindow(), *_players[0]);
            int roomer = _players[0]->getRoom();

            switch(roomissue) {
                case ReturnRoom::Continue:
                    isLooping = false;
                    cout << "Continue" << endl;
                    break;
                case ReturnRoom::Back:
                    cout << "Back" << endl;
                    break;
                case ReturnRoom::Salle:
                    cout << "Salle" << endl;
                    RoomMenu().creatingGame(_windowhdl->getWindow(), _players, _netTCP, roomer, false);
                    break;
            }
        } else if (mainissue == Quit)
            return false;
    }
    _environment->setPlayerName(_players[0]->getName());
    return true;
}

void Client::waitConnection(void) {
    sf::Event event;
    int attempt = -3;
    network::UDPMessage _msgCoUdp = {-1, {84}, network::Event::ADD};
    network::TCPMessage _msgCoTcp = {network::TCPEvent::CREATE_ROOM, {-1}};
    shared_ptr<ImageSFML> waiter = make_shared<ImageSFML>("./resources/sprites/background.png");
    shared_ptr<TextSfml> textw = make_shared<TextSfml>("Wait for Server...", "./resources/fonts/2MASS.otf", sf::Color::White, 950 - 99, 850);

    for (size_t frame = 0; !_netTCP.isConnected() && _windowhdl->isOpen(); frame ++) {
        while (_windowhdl->getWindow()->pollEvent(event))
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                _windowhdl->close();
        if (frame > (attempt > 0 ? 300 : 60)) {
            frame = 0;
            attempt ++;
        }
        textw->setString("Wait for Server..." + (attempt > 0 ? "(attempt " + to_string(attempt) + ")" : ""));
        _windowhdl->getWindow()->draw(*waiter->getSprite());
        _windowhdl->getWindow()->draw(*textw->getData());
        _windowhdl->display();
    }
}

void Client::setRoomNbr(int nbr) {_roomNbr = nbr;}
MusicSystem Client::getMusicSystem(void) const {return _musics;}
bool Client::isTCPConnected(void) {return _netTCP.isConnected();}
network::NetUDPClient &Client::getNetworkUDP(void) {return _netUDP;}
size_t Client::getNumbersPlayer(void) const {return _players.size();}
shared_ptr<client::WindowHandler> Client::getWindowHandler(void) const {return _windowhdl;}
shared_ptr<client::Player> Client::getPlayer(size_t row) const {return row > 4 ? nullptr : _players[row];}
