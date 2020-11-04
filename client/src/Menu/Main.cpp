#include "Main.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

Mainmenu::Mainmenu() {
    _name = "";
    isHost = false;
    isJoin = false;
    _host = make_shared<Button>(sf::Vector2f((1900 - 250) / 2, 250), sf::Vector2f(250, 100));
    _join = make_shared<Button>(sf::Vector2f((1900 - 250) / 2, 400), sf::Vector2f(250, 100));

    _host->setColor(sf::Color::Black, sf::Color::White, 5);
    _join->setColor(sf::Color::Black, sf::Color::White, 5);
    _host->setText("./resources/fonts/2MASS.otf", "Host", 75, sf::Color::White);
    _join->setText("./resources/fonts/2MASS.otf", "Join", 75, sf::Color::White);
}
Mainmenu::~Mainmenu() {}

ReturnMain Mainmenu::loop(shared_ptr<sf::RenderWindow> _window, Player &player) {
    ImageSFML back("./resources/sprites/mainbackground.png");
    TextSfml name_txt("Pseudo: " + _name, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _window->setFramerateLimit(60);
    while(_window->isOpen() && !isHost && !isJoin) {
        EventHandler(_window);

        name_txt.setString("Pseudo: " + _name);
        name_txt.setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back.getSprite());
        _window->draw(*name_txt.getData());
        _host->drawButton(_window);
        _join->drawButton(_window);
        _window->display();
        _window->clear();
    }
    player.setName(_name);
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
            // else if (event.key.code == 58 || event.key.code == 48)
            //     isMenu = false;
        } if (_host->isClicked(event))
            isHost = true;
        else if (_join->isClicked(event))
            isJoin = true;
    }
}