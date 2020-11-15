/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

client::Player::Player(int id) {
    _id = id;
    _room = -1;
    _name = "";
    isAdmin = false;
    _image = make_shared<ImageSFML>("./resources/sprites/r-typesheet42.gif");
    _textname = make_shared<TextSfml>(_name, "./resources/fonts/2MASS.otf", sf::Color::White, 840, 880);

    _textname->setSize(15);

    _image->getSprite()->setTextureRect(sf::IntRect(0, 0, 33, 17));
    _image->getSprite()->setScale(sf::Vector2f(3, 3));
    _image->getSprite()->setPosition(sf::Vector2f(250, 250));
}
client::Player::~Player() {
}

void client::Player::setPosition(sf::Vector2f newpos) {
    newpos = newpos.x < 0 ? sf::Vector2f(0, newpos.y) : (newpos.y < 0 ? sf::Vector2f(newpos.x, 0) : newpos);
    _image->getSprite()->setPosition(newpos);
    _textname->setPosition(sf::Vector2f(840, 880));
}

void client::Player::setName(string str) {
    _name = str;
    _textname->setString(_name);
}

void client::Player::setId(int id) {_id = id;}
int client::Player::getRoom(void) {return _room;}
int client::Player::getId(void) const {return _id;}
void client::Player::setRoom(int room) {_room = room;}
string client::Player::getName(void) const {return _name;}
bool client::Player::getAdmin(void) const {return isAdmin;}
void client::Player::setAdmin(bool boolean) {isAdmin = boolean;}
shared_ptr<client::ImageSFML> client::Player::getImage(void) const {return _image;}
shared_ptr<client::TextSfml> client::Player::getNameText(void) const {return _textname;}
void client::Player::setImage(ImageSFML news) {_image = make_shared<client::ImageSFML>(news);}