/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Room Menu
*/

#include "Room.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

void addItems(vector<shared_ptr<Button>> &roomlist, size_t row) {
    roomlist.push_back(make_shared<Button>(sf::Vector2f(955 - 125, 250 + (row * 110)), sf::Vector2f(250, 100)));
    roomlist[row]->setColor(sf::Color::Black, sf::Color::White, 5);
    roomlist[row]->setText("./resources/fonts/2MASS.otf", "R. " + to_string(row + 1), 75, sf::Color::White);
}

RoomMenu::RoomMenu(string name, size_t ndx) {
    _name = "";
    isMenu = true;
    size_t row = 0;

    for (; row < ndx; row ++)
        addItems(roomlist, row);
}
RoomMenu::~RoomMenu() {}

ReturnRoom RoomMenu::loop(shared_ptr<sf::RenderWindow> _window, Player &player) {
    sf::Event event;
    ImageSFML back("./resources/sprites/mainbackground.png");
    TextSfml name_txt("Pseudo: " + player.getName(), "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _name = player.getName();
    _window->setFramerateLimit(60);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window, player);

        name_txt.setString("Pseudo: " + _name);
        name_txt.setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back.getSprite());
        _window->draw(*name_txt.getData());
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
            if (roomlist[i]->isClicked(event))
                player.setRoom(i + 1);
        }
    }
}

ReturnRoom RoomMenu::creatingGame(shared_ptr<sf::RenderWindow> _window, Player &player) {
    sf::Event event;
    string roomname = "Partie de " + player.getName();
    ImageSFML back("./resources/sprites/mainbackground.png");
    ImageSFML P1("./resources/sprites/mainbackground.png");
    ImageSFML P2("./resources/sprites/mainbackground.png");
    ImageSFML P3("./resources/sprites/mainbackground.png");
    ImageSFML P4("./resources/sprites/mainbackground.png");
    TextSfml name_txt(roomname, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _name = roomname;
    _window->setFramerateLimit(60);
    while(_window->isOpen()) {
        EventHandler(_window, player);

        name_txt.setString("Nom de la Partie: " + _name);
        name_txt.setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back.getSprite());
        _window->draw(*name_txt.getData());

        _window->display();
        _window->clear();
        while(_window->pollEvent(event))
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return Back;
    }
    return player.getRoom() == 0 ? Continue : Back;
}