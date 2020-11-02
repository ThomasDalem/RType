/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

Player::Player() {
    _name = "";
    _image = make_shared<ImageSFML>("./resources/sprites/r-typesheet42.gif");

    _image->getSprite()->setTextureRect(sf::IntRect(0, 0, 33, 17));
    _image->getSprite()->setScale(sf::Vector2f(3, 3));
    _image->getSprite()->setPosition(sf::Vector2f(250, 250));
}
Player::~Player() {}

string Player::getName(void) const {return _name;}
void Player::setName(string str) {this->_name = str;}
void Player::setHealth(size_t hlth) {_health = hlth;}
size_t Player::getHealth(void) const {return _health;}
ImageSFML Player::getImage(void) const {return *_image;}
void Player::setImage(ImageSFML news) {_image = make_shared<ImageSFML>(news);}