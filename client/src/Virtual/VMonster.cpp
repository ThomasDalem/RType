/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Virtual Monster
*/

#include "VMonster.hpp"

VMonster::VMonster() {}
VMonster::~VMonster() {}

void VMonster::operator=(VMonster another) {
    health = another.health;
    _image = make_shared<ImageSFML>(another._image->getPath());
}

bool VMonster::operator==(VMonster another) {
    if (health != another.health)
        return false;
    else if (_image != another._image)
        return false;
    return true;
}

void VMonster::shoot(void) {}
