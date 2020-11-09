/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Image SFML
*/

#include <iostream>
#include "ImageSFML.hpp"

using namespace std;
ImageSFML::ImageSFML(string path) {
    _path = path;
    _sprite = make_shared<sf::Sprite>();
    _texture = make_shared<sf::Texture>();

    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite->setTexture(*_texture);
}
ImageSFML::~ImageSFML() {
    _texture->~Texture();
}

void ImageSFML::setTexture(string path) {
    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite->setTexture(*_texture);
}

string ImageSFML::getPath() const {return _path;}
shared_ptr<sf::Sprite> ImageSFML::getSprite() const {return(_sprite);}
void ImageSFML::setPosition(sf::Vector2f pos) {_sprite->setPosition(pos);}
void ImageSFML::setScale(sf::Vector2f size) {this->_sprite->setScale(size);}
void ImageSFML::setSprite(sf::Sprite newone) {this->_sprite = make_shared<sf::Sprite>(newone);}