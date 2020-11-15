/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Room Menu
*/

#include "Room.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "ManetteSFML.hpp"

using namespace client;
using namespace network;
RoomMenu::RoomMenu(string name, size_t ndx) {
    _name = "";
    isMenu = true;
    isPlay = false;
    size_t row = 0;
    _play = make_shared<Button>(sf::Vector2f((1900 - 250) / 2, 700), sf::Vector2f(250, 100));

    _play->setColor(sf::Color::Black, sf::Color::White, 5);
    _play->setText("./resources/fonts/2MASS.otf", "Play", 75, sf::Color::White);
    for (; row < ndx; row ++)
        addItems(roomlist, row);
}
RoomMenu::~RoomMenu() {}

void RoomMenu::addItems(vector<shared_ptr<Button>> &roomlist, size_t row) {
    roomlist.push_back(make_shared<Button>(sf::Vector2f(955 - 125, 250 + (row * 110)), sf::Vector2f(250, 100)));
    roomlist[row]->setColor(sf::Color::Black, sf::Color::White, 5);
    roomlist[row]->setText("./resources/fonts/2MASS.otf", "R. " + to_string(row + 1), 75, sf::Color::White);
}

ReturnRoom RoomMenu::loop(shared_ptr<sf::RenderWindow> _window, Player &player) {
    sf::Event event;
    ManetteSFML Remote;
    shared_ptr<ImageSFML> choice = make_shared<ImageSFML>("./resources/sprites/choice.png");
    shared_ptr<ImageSFML> arrow = make_shared<ImageSFML>("./resources/sprites/arrow_back.png");
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("./resources/sprites/mainbackground.png");
    shared_ptr<TextSfml> name_txt = make_shared<TextSfml>("Pseudo: " + player.getName(), "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    arrow->setScale(sf::Vector2f(0.25, 0.25));
    choice->setScale(sf::Vector2f(0.05, 0.05));
    choice->setRotate(-90);
    choice->setPosition(sf::Vector2f(600, 500));
    _name = player.getName();
    _window->setFramerateLimit(60);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window, player);
        name_txt->setString("Pseudo: " + _name);
        name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back->getSprite());
        _window->draw(*arrow->getSprite());
        _window->draw(*name_txt->getData());
        if (Remote.isConnected())
            _window->draw(*choice->getSprite());
        for (size_t i = 0; i < roomlist.size(); i ++)
            roomlist[i]->drawButton(_window);
        _window->display();
        _window->clear();

        if (player.getRoom() != -1)
            break;
        while(_window->pollEvent(event))
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                _window->close();
        if (arrow->isClicked(event, _window))
            return Back;
    }
    return player.getRoom() >= 0 ? Salle : Back;
}

void RoomMenu::EventHandler(shared_ptr<sf::RenderWindow> _window, Player &player) {
    sf::Event event;

    while(_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == 59 && _name.length() > 0)
                _name = _name.substr(0, _name.length() - 1);
            else if (event.key.code < 26 && event.key.shift)
                _name = _name + (char)(event.key.code + 65);
            else if (event.key.code < 26)
                _name = _name + (char)(event.key.code + 97);
            else if (event.key.code == 57)
                _name = _name + " ";
        } for (size_t i = 0; i < roomlist.size(); i ++) {
            if (roomlist[i]->isClicked(event, _window)) {
                player.setRoom(i + 1);
                cout << "Playing Room set:" << i << endl;
            }
        }
    }
}

ReturnRoom RoomMenu::creatingGame(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Player>> &players, NetTCPClient &client, int &roomNbr, bool admin) {
    sf::Event event;
    ManetteSFML Remote;
    TCPMessage message = {TCPEvent::CREATE_ROOM, {0}};
    string roomname = "Partie de " + players[0]->getName();
    shared_ptr<ImageSFML> choice = make_shared<ImageSFML>("./resources/sprites/choice.png");
    shared_ptr<ImageSFML> arrow = make_shared<ImageSFML>("./resources/sprites/arrow_back.png");
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("./resources/sprites/mainbackground.png");
    shared_ptr<TextSfml> name_txt = make_shared<TextSfml>(roomname, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    if (admin) {
        memcpy(message.data, roomname.c_str(), roomname.length() + 1);
        client.sendMessage(message);
        while (!client.hasMessages());
        while (client.hasMessages()) {
            unique_ptr<TCPMessage> receivedMessage = client.getFirstMessage();
            if (receivedMessage->event == TCPEvent::CREATE_ROOM) {
                cout << "Room " << int(receivedMessage->data[0]) << " created" << endl;
                roomNbr = int(receivedMessage->data[0]);
                message.event = TCPEvent::CONNECT;
                message.data[0] = receivedMessage->data[0];
                client.sendMessage(message);
            }
        }
    } else {
        roomNbr = 0;
        TCPMessage connecter = {TCPEvent::CONNECT, {(char)roomNbr}};

        memcpy(&connecter.data[1], players[0]->getName().c_str(), players[0]->getName().length() + 1);
        client.sendMessage(message);
    }
    cout << "Connected to room " << roomNbr << endl;
    arrow->setScale(sf::Vector2f(0.25, 0.25));
    choice->setScale(sf::Vector2f(0.05, 0.05));
    choice->setRotate(-90);
    choice->setPosition(sf::Vector2f(650, 800));
    name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));
    _name = roomname;
    _window->setFramerateLimit(60);
    for (size_t frame = 0; _window->isOpen() && !isPlay; frame ++) {
        EventHandler(_window, *players[0]);
        name_txt->setString("Nom de la Partie: " + _name);
        name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back->getSprite());
        _window->draw(*arrow->getSprite());
        if (Remote.isConnected())
            _window->draw(*choice->getSprite());
        _window->draw(*name_txt->getData());
        for (size_t i = 0; i < players.size(); i ++) {
            players[i]->setPosition(sf::Vector2f(800, 250 + (i * 50)));
            players[i]->getNameText()->setSize(30);
            players[i]->getNameText()->setPosition(sf::Vector2f(800 - (players[i]->getNameText()->getData()->getString().getSize() * 30), 265 + (i * 50)));

            _window->draw(*players[i]->getImage()->getSprite());
            _window->draw(*players[i]->getNameText()->getData());
        } if (admin)
            _play->drawButton(_window);
        _window->display();
        _window->clear();
        while(_window->pollEvent(event) && frame > 30) {
            if (Remote.isClicked(ManetteSFML::Button::Croix))
                return Continue;
            if (Remote.isClicked(ManetteSFML::Button::Carre))
                return Back;
            EventHandler(_window, *players[0]);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                _window->close();
            if (arrow->isClicked(event, _window))
                return Back;
            if (admin && _play->isClicked(event, _window)) {
                TCPMessage startMessage = {TCPEvent::START, {char(roomNbr)}};
                client.sendMessage(startMessage);
                while (!client.hasMessages());
                while (client.hasMessages()) {
                    unique_ptr<TCPMessage> receivedMessage = client.getFirstMessage();
                    if (receivedMessage->event == TCPEvent::START)
                        return Continue;
                }
                return Continue;
            }
        }
    }
    return Continue;
}