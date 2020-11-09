/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(size_t id) {
    _id = id;
    _room = -1;
    _name = "";
    _image = make_shared<ImageSFML>("./resources/sprites/r-typesheet42.gif");
    _textname = make_shared<TextSfml>(_name, "./resources/fonts/2MASS.otf", sf::Color::White, 250, 250 - 15);

    _textname->setSize(15);
    _image->getSprite()->setTextureRect(sf::IntRect(0, 0, 33, 17));
    _image->getSprite()->setScale(sf::Vector2f(3, 3));
    _image->getSprite()->setPosition(sf::Vector2f(250, 250));
}
Player::~Player() {}

void Player::setPosition(sf::Vector2f newpos) {
    newpos = newpos.x < 0 ? sf::Vector2f(0, newpos.y) : (newpos.y < 0 ? sf::Vector2f(newpos.x, 0) : newpos);
    _image->getSprite()->setPosition(newpos);
    _textname->setPosition(sf::Vector2f(newpos.x, newpos.y - 15));
}

void Player::setName(string str) {
    _name = str;
    _textname->setString(_name);
}

void Player::setRoom(int room) {_room = room;}
int Player::getRoom(void) const {return _room;}
void Player::setId(size_t id) {_id = id;}
size_t Player::getId(void) const {return _id;}
string Player::getName(void) const {return _name;}
shared_ptr<ImageSFML> Player::getImage(void) const {return _image;}
shared_ptr<TextSfml> Player::getNameText(void) const {return _textname;}
void Player::setImage(ImageSFML news) {_image = make_shared<ImageSFML>(news);}