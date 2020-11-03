/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Window Handler
*/

#include "WindowHandler.hpp"

WindowHandler::WindowHandler(size_t width, size_t height, string name, size_t fps) {
    _width = 0;
    _height = 0;
    _window = make_shared<sf::RenderWindow>(sf::VideoMode(1200, 600), "R-Type");
    _background = new Background();

    auto appIcon = sf::Image {};
     if (!appIcon.loadFromFile("resources/sprites/icon.png"))
            cout << "Loading Ressource Failed" << endl;
    _window->setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());
}

WindowHandler::~WindowHandler() {
    _texts.clear();
    _images.clear();
}

void WindowHandler::display(void) const {
    _window->draw(*_background->getImage()->getSprite());

    _window->display();
    _window->clear();
}

void WindowHandler::rmText(size_t row) {
    size_t i = 0;

    for (; i < _texts.size() && i < row; i ++);
    _texts.erase(_texts.begin() + i);
}

void WindowHandler::rmImage(size_t row) {
    size_t i = 0;

    for (; i < this->_images.size() && i < row; i ++);
    _images.erase(_images.begin() + i);
}

size_t WindowHandler::getWidth(void) const {return _width;}
string WindowHandler::getTitle(void) const {return _title;}
size_t WindowHandler::getHeight(void) const {return _height;}
void WindowHandler::setWidth(size_t width) {this->_width = width;}
void WindowHandler::setTitle(string title) {this->_title = title;}
bool WindowHandler::isOpen(void) const {return _window->isOpen();}
void WindowHandler::setHeight(size_t height) {this->_height = height;}
Background *WindowHandler::getBackground(void) const {return this->_background;}
void WindowHandler::setFramerate(size_t fps) const {_window->setFramerateLimit(fps);}
void WindowHandler::addText(TextSfml news) {_texts.push_back(make_shared<TextSfml>(news));}
void WindowHandler::addImage(ImageSFML news) {_images.push_back(make_shared<ImageSFML>(news));}