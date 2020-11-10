/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client Entities
*/

#include "Entities.hpp"

Entities::Entities(int id, size_t type) {
    _id = id;

    switch(type) {
        case 0: _path = "./resources/sprites/r-typesheet42.gif"; break; // Player
        case 1: _path = "./resources/sprites/r-typesheet1.gif"; break; // Bullet
        case 2: _path = "./resources/sprites/r-typesheet18.gif"; break; // Environnement
        // case 3: _path = "./resources/sprites/r-typesheet18.gif"; break; // Music
        case 4: _path = "./resources/sprites/power_up.png"; break; // Power Up
        case 5: _path = "./resources/sprites/block.png"; break; // Destroyable
        case 6: _path = "./resources/sprites/block.png"; break; // StageObstacle
        case 7: _path = "./resources/sprites/r-typesheet18.gif"; break; // Alien
        case 8: _path = "./resources/sprites/r-typesheet26.gif"; break; // Battleshibre
        case 9: _path = "./resources/sprites/r-typesheet20.gif"; break; // Trooper
    }
    _type = type;
    _image = make_shared<ImageSFML>(_path);
}
Entities::~Entities() {}

void Entities::setId(int id) {_id = id;}
int Entities::getId(void) const {return _id;}
shared_ptr<ImageSFML> Entities::getImage(void) const {return _image;}
