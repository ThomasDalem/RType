#include "Main.hpp"
#include "TextSFML.hpp"

Mainmenu::Mainmenu() {
    _name = "";
    isMenu = true;
}
Mainmenu::~Mainmenu() {}

string Mainmenu::loop(shared_ptr<sf::RenderWindow> _window) {
    TextSfml name_txt(_name, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _window->setFramerateLimit(30);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window);

        name_txt.setString(_name);
        name_txt.setPosition(sf::Vector2f(600 - ((_name.length() / 2) * 15), 25));

        _window->draw(*name_txt.getData());
        _window->display();
        _window->clear();
    }
    return _name;
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
            else if (event.key.code == 58 || event.key.code == 48)
                isMenu = false;
        }
    }
}