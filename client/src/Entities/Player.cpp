/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

Player::Player() {
    _name = "";
    _pos = sf::Vector2f(250, 250);
    _image = make_shared<ImageSFML>("./resources/sprites/r-typesheet42.gif");

    _image->getSprite()->setTextureRect(sf::IntRect(0, 0, 33, 17));
    _image->getSprite()->setScale(sf::Vector2f(3, 3));
    _image->getSprite()->setPosition(_pos);
}
Player::~Player() {}

void Player::setPosition(sf::Vector2f newpos) {
    newpos = newpos.x < 0 ? sf::Vector2f(0, newpos.y) : (newpos.y < 0 ? sf::Vector2f(newpos.x, 0) : newpos);
    _pos = newpos;
    _image->getSprite()->setPosition(_pos);
}

string Player::getName(void) const {return _name;}
void Player::setName(string str) {this->_name = str;}
void Player::setHealth(size_t hlth) {_health = hlth;}
size_t Player::getHealth(void) const {return _health;}
ImageSFML Player::getImage(void) const {return *_image;}
sf::Vector2f Player::getPosition(void) const {return _pos;}
void Player::setImage(ImageSFML news) {_image = make_shared<ImageSFML>(news);}