#include "Main.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

#include <stdio.h>
#include <stdlib.h>

string randomGen(void) {
    switch(rand() % 10) {
        case 0: return "Superman" + to_string(rand() % 100); break;
        case 1: return "Batman" + to_string(rand() % 100); break;
        case 2: return "Babar" + to_string(rand() % 100); break;
        case 3: return "Jafare" + to_string(rand() % 100); break;
        case 4: return "Franklin" + to_string(rand() % 100); break;
        case 5: return "Oggy" + to_string(rand() % 100); break;
        case 6: return "Rocket" + to_string(rand() % 100); break;
        case 7: return "Didier" + to_string(rand() % 100); break;
        case 8: return "Jacky" + to_string(rand() % 100); break;
        case 9: return "XxDarkKikoudu91xx"; break;
        default: return "KevinDu16"; break;
    }
    return "Genius5000";
}

Mainmenu::Mainmenu() {
    _name = "";
    isHost = false;
    isJoin = false;
    isQuit = false;
    _host = make_shared<Button>(sf::Vector2f((1900 - 250) / 2, 250), sf::Vector2f(250, 100));
    _join = make_shared<Button>(sf::Vector2f((1900 - 250) / 2, 400), sf::Vector2f(250, 100));

    _host->setColor(sf::Color::Black, sf::Color::White, 5);
    _join->setColor(sf::Color::Black, sf::Color::White, 5);
    _host->setText("./resources/fonts/2MASS.otf", "Host", 75, sf::Color::White);
    _join->setText("./resources/fonts/2MASS.otf", "Join", 75, sf::Color::White);
}
Mainmenu::~Mainmenu() {}

ReturnMain Mainmenu::loop(shared_ptr<sf::RenderWindow> _window, Player &player) {
    shared_ptr<ImageSFML> arrow = make_shared<ImageSFML>("./resources/sprites/arrow_back.png");
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("./resources/sprites/mainbackground.png");
    shared_ptr<TextSfml> name_txt = make_shared<TextSfml>("Pseudo: " + _name, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    arrow->setScale(sf::Vector2f(0.25, 0.25));
    _window->setFramerateLimit(60);
    while(_window->isOpen() && !isHost && !isJoin && !isQuit) {
        EventHandler(_window);

        name_txt->setString("Pseudo: " + _name);
        name_txt->setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back->getSprite());
        _window->draw(*arrow->getSprite());
        _window->draw(*name_txt->getData());
        _host->drawButton(_window);
        _join->drawButton(_window);
        _window->display();
        _window->clear();
    }
    player.setName(_name == "" ? randomGen() : _name);
    return isJoin ? Room : (isHost ? Creating : Quit);
}

void Mainmenu::EventHandler(shared_ptr<sf::RenderWindow> _window) {
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
        } if (_host->isClicked(event, _window))
            isHost = true;
        else if (_join->isClicked(event, _window))
            isJoin = true;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            isQuit = true;
    }
}