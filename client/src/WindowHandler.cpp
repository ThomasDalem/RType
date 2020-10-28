#include "WindowHandler.hpp"

WindowHandler::WindowHandler(size_t width, size_t height, string name, size_t fps) {
    _width = 0;
    _height = 0;
    _window = make_shared<sf::RenderWindow>(sf::VideoMode(1200, 600), "R-Type");
}
WindowHandler::~WindowHandler() {

}

void WindowHandler::display(void) const {
    _window->display();
    _window->clear();
}

bool WindowHandler::isOpen(void) const {return _window->isOpen();}

void WindowHandler::setWidth(size_t width) {this->_width = width;}
void WindowHandler::setHeight(size_t height) {this->_height = height;}
void WindowHandler::setTitle(string title) {this->_title = title;}

size_t WindowHandler::getWidth(void) const {return _width;}
size_t WindowHandler::getHeight(void) const {return _height;}
string WindowHandler::getTitle(void) const {return _title;}

void WindowHandler::setFramerate(size_t fps) const {_window->setFramerateLimit(fps);}