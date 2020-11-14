/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Image SFML
*/

#include <iostream>
#include "ImageSFML.hpp"

using namespace std;
client::ImageSFML::ImageSFML(string path) {
    _path = path;
    _sprite = make_shared<sf::Sprite>();
    _texture = make_shared<sf::Texture>();

    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite->setTexture(*_texture);
}
client::ImageSFML::~ImageSFML() {
}

void client::ImageSFML::setTexture(string path) {
    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite->setTexture(*_texture);
}

void client::ImageSFML::setRectangleSheep(sf::IntRect rect) {
    _sprite->setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
}

int client::ImageSFML::isClicked(sf::Event event, shared_ptr<sf::RenderWindow> window) {
    sf::Vector2i cursorPos;
    sf::Vector2i windowPos = window->getPosition();

    if (event.type == sf::Event::MouseButtonPressed) {
        cursorPos = sf::Mouse::getPosition();
        if (_sprite->getGlobalBounds().contains(sf::Vector2f(cursorPos.x - windowPos.x, cursorPos.y - windowPos.y)))
            return true;
    }
    return false;
}

string client::ImageSFML::getPath() const {return _path;}
void client::ImageSFML::setRotate(int rot) {_sprite->setRotation(rot);}
shared_ptr<sf::Sprite> client::ImageSFML::getSprite() const {return(_sprite);}
void client::ImageSFML::setPosition(sf::Vector2f pos) {_sprite->setPosition(pos);}
void client::ImageSFML::setScale(sf::Vector2f size) {this->_sprite->setScale(size);}
sf::IntRect client::ImageSFML::getRectangleSheep() const {return (_sprite->getTextureRect());};
void client::ImageSFML::setSprite(sf::Sprite newone) {this->_sprite = make_shared<sf::Sprite>(newone);}
