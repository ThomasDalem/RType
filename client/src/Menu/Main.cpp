#include "Main.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

Mainmenu::Mainmenu() {
    _name = "";
    isMenu = true;
    _play = make_shared<Button>(sf::Vector2f(500, 250), sf::Vector2f(250, 100));

    _play->setColor(sf::Color::Black, sf::Color::White, 5);
    _play->setText("./resources/fonts/2MASS.otf", "Play", 75, sf::Color::White);
}
Mainmenu::~Mainmenu() {}

string Mainmenu::loop(shared_ptr<sf::RenderWindow> _window) {
    ImageSFML back("./resources/sprites/mainbackground.png");
    TextSfml name_txt("Pseudo: " + _name, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    back.setScale(sf::Vector2f(0.75, 0.5));
    _window->setFramerateLimit(60);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window);

        name_txt.setString("Pseudo: " + _name);
        name_txt.setPosition(sf::Vector2f(590 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back.getSprite());
        _window->draw(*name_txt.getData());
        _play->drawButton(_window);
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
            // else if (event.key.code == 58 || event.key.code == 48)
            //     isMenu = false;
        } if (_play->isClicked(event))
            isMenu = false;
    }
}