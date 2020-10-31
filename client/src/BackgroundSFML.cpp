/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Background
*/

#include "BackgroundSFML.hpp"

Background::Background() {
    _image = make_shared<ImageSFML>("./resources/sprites/background.png");
}
Background::~Background() {}

void Background::stop(void) const {}
void Background::move(void) const {}
void Background::speedUp(size_t sp) const {}
shared_ptr<ImageSFML> Background::getImage(void) const {return _image;}
