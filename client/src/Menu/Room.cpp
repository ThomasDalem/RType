/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Room Menu
*/

#include "Room.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

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
    shared_ptr<ImageSFML> arrow = make_shared<ImageSFML>("./resources/sprites/arrow_back.png");
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("./resources/sprites/mainbackground.png");
    shared_ptr<TextSfml> name_txt = make_shared<TextSfml>("Pseudo: " + player.getName(), "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    arrow->setScale(sf::Vector2f(0.25, 0.25));
    _name = player.getName();
    _window->setFramerateLimit(60);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window, player);

        name_txt->setString("Pseudo: " + _name);
        name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back->getSprite());
        _window->draw(*arrow->getSprite());
        _window->draw(*name_txt->getData());
        for (size_t i = 0; i < roomlist.size(); i ++)
            roomlist[i]->drawButton(_window);
        _window->display();
        _window->clear();

        if (player.getRoom() != -1)
            break;
        while(_window->pollEvent(event))
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return Back;
    }
    return player.getRoom() > 0 ? Salle : Back;
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
            if (roomlist[i]->isClicked(event, _window))
                player.setRoom(i + 1);
        } if (_play->isClicked(event, _window))
            isPlay = true;
    }
}

ReturnRoom RoomMenu::creatingGame(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Player>> players) {
    sf::Event event;
    string roomname = "Partie de " + players[0]->getName();
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("./resources/sprites/mainbackground.png");
    shared_ptr<TextSfml> name_txt = make_shared<TextSfml>(roomname, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _name = roomname;
    _window->setFramerateLimit(120);
    while(_window->isOpen() && !isPlay) {
        EventHandler(_window, *players[0]);

        name_txt->setString("Nom de la Partie: " + _name);
        name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back->getSprite());
        _window->draw(*name_txt->getData());
        for (size_t i = 0; i < players.size(); i ++) {
            players[i]->setPosition(sf::Vector2f(800, 250 + (i * 50)));
            players[i]->getNameText()->setSize(30);
            players[i]->getNameText()->setPosition(sf::Vector2f(800 - (players[i]->getNameText()->getData()->getString().getSize() * 30), 265 + (i * 50)));

            _window->draw(*players[i]->getImage()->getSprite());
            _window->draw(*players[i]->getNameText()->getData());
        }
        _play->drawButton(_window);
        _window->display();
        _window->clear();
        while(_window->pollEvent(event)) {
            EventHandler(_window, *players[0]);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                return Back;
        }
    }
    return Continue;
}