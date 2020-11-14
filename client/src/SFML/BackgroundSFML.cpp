/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Background
*/

#include "BackgroundSFML.hpp"

using namespace std;
client::Background::Background(int refresh) {
    _position = 0;
    _refresh = refresh;
    _movement = refresh == 0 ? false : true;
    _image = make_shared<ImageSFML>("./resources/sprites/background.png");
}
client::Background::~Background() {
}

void client::Background::move(void) {
    if (this->_movement) {
        this->_position -= 3;
        if (this->_position < _refresh)
            this->_position = 0;
        _image->setPosition(sf::Vector2f(_position, 0));
    }
}

void client::Background::speedUp(int sp) {
    if (sp == 0)
        _movement = false;
    else
        _refresh = sp;
}

void client::Background::stop(void) {_movement = false;}
shared_ptr<client::ImageSFML> client::Background::getImage(void) const {return _image;}
