/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Background
*/

#include "BackgroundSFML.hpp"

using namespace std;
Background::Background(int refresh) {
    _position = 0;
    _refresh = refresh;
    _image = make_shared<ImageSFML>("./resources/sprites/background.png");
}
Background::~Background() {}

void Background::stop(void) const {}
void Background::move(void) {
    this->_position -= 3;
    if (this->_position < _refresh) {
        this->_position = 0;
        cout << "Background Update" << endl;
    }
    _image->setPosition(sf::Vector2f(_position, 0));
}
void Background::speedUp(size_t sp) const {}
shared_ptr<ImageSFML> Background::getImage(void) const {return _image;}
