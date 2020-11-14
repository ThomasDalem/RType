/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Window Handler
*/

#include "WindowHandler.hpp"

client::WindowHandler::WindowHandler(size_t width, size_t height, string name, size_t fps) {
    _width = width;
    _height = height;
    _window = make_shared<sf::RenderWindow>(sf::VideoMode(_width, _height), "R-Type");
    _background = make_shared<Background>(-1914);

    auto appIcon = sf::Image {};
    if (!appIcon.loadFromFile("resources/sprites/icon.png"))
        cout << "Loading Ressource Failed" << endl;
    _window->setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());
}

client::WindowHandler::~WindowHandler() {
}

void client::WindowHandler::dispBackground() {
    _background->move();

    _window->draw(*_background->getImage()->getSprite());
    for (size_t i = 0; i < _texts.size() && i < _texts.size(); i ++)
        _window->draw(*_texts[i]->getData());
}

void client::WindowHandler::dispEnvironment(std::shared_ptr<client::Environment> &environment) const
{
    sf::RectangleShape hudBack = sf::RectangleShape(sf::Vector2f(300, 150));

    hudBack.setFillColor(sf::Color::Black);
    hudBack.setOutlineColor(sf::Color::White);
    hudBack.setOutlineThickness(1);
    hudBack.setPosition(810, 850);
    _window->draw(hudBack);
    environment->getHealthText()->setString("health: " + to_string(environment->getHealth()));
    environment->getScoreText()->setString("score: " + to_string(environment->getScore()));
    _window->draw(*environment->getPlayerSprite()->getSprite());
    _window->draw(*environment->getScoreText()->getData());
    _window->draw(*environment->getHealthText()->getData());
    _window->draw(*environment->getPlayerName()->getData());
}


void client::WindowHandler::dispEntities(vector<shared_ptr<client::Entities>> entities) const
{
    for (size_t i = 0; i < entities.size(); i ++)
        _window->draw(*entities[i]->getImage()->getSprite());
}

void client::WindowHandler::display() const {
    _window->display();
    _window->clear();
}

void client::WindowHandler::rmText(size_t row) {
    size_t i = 0;

    for (; i < _texts.size() && i < row; i ++);
    _texts.erase(_texts.begin() + i);
}

void client::WindowHandler::rmImage(size_t row) {
    size_t i = 0;

    for (; i < this->_images.size() && i < row; i ++);
    _images.erase(_images.begin() + i);
}

client::Input client::WindowHandler::isEvent(client::Player &player) {
    sf::Event event;
    sf::Joystick joys;
    size_t sensybility = 80;

    if (joys.isConnected(0)) {
        joys.update();
        sf::Vector2f Jpos(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

        // 0 = croix
        // 1 = rond
        // 2 = Carré
        // 3 = Triangle

        // cout << "Button 4 pressed: " << (joys.isButtonPressed(0, 4) ? "true" : "false") << endl;
        if (joys.isButtonPressed(0, 0))
            return Shoot;
        if (Jpos.x > sensybility)
            return Left;
        if (Jpos.x < (int)(-1 * sensybility))
            return Right;
        if (Jpos.y > sensybility)
            return Down;
        if (Jpos.y < (int)(-1 * sensybility))
            return Up;
    } else {
        while (_window->pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                _window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                return RightUp;
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                return LeftUp;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                return RightDown;
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                return LeftDown;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return Up;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return Down;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                return Left;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                return Right;
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                return Shoot;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                return Escape;
        }
    }
    return Nothing;
}

void client::WindowHandler::close() {_window->close();}
size_t client::WindowHandler::getWidth(void) const {return _width;}
string client::WindowHandler::getTitle(void) const {return _title;}
size_t client::WindowHandler::getHeight(void) const {return _height;}
void client::WindowHandler::setWidth(size_t width) {this->_width = width;}
void client::WindowHandler::setTitle(string title) {this->_title = title;}
bool client::WindowHandler::isOpen(void) const {return _window->isOpen();}
void client::WindowHandler::setHeight(size_t height) {this->_height = height;}
void client::WindowHandler::addText(shared_ptr<TextSfml> news) {_texts.push_back(news);}
shared_ptr<sf::RenderWindow> client::WindowHandler::getWindow(void) const {return _window;}
void client::WindowHandler::addImage(shared_ptr<ImageSFML> news) {_images.push_back(news);}
void client::WindowHandler::setFramerate(size_t fps) const {_window->setFramerateLimit(fps);}
shared_ptr<client::Background> client::WindowHandler::getBackground(void) const {return _background;}
