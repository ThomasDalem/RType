/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client Entities
*/

#include "Entities.hpp"

client::Entities::Entities(int id, size_t type, string name) {
    _id = id;
    _name = name;

    switch(type) {
        case 0: _path = "./resources/sprites/r-typesheet42.gif"; break; // Player
        case 1: _path = "./resources/sprites/r-typesheet1.gif"; break; // Bullet
        case 2: _path = "./resources/sprites/r-typesheet18.gif"; break; // Environnement
        // case 3: _path = "./resources/sprites/r-typesheet18.gif"; break; // Music
        case 4: _path = "./resources/sprites/block.png"; break; // Power Up
        case 5: _path = "./resources/sprites/block.png"; break; // Destroyable
        case 6: _path = "./resources/sprites/block.png"; break; // StageObstacle
        case 7: _path = "./resources/sprites/r-typesheet18.gif"; break; // Alien
        case 8: _path = "./resources/sprites/r-typesheet26.gif"; break; // Battleshibre
        case 9: _path = "./resources/sprites/r-typesheet20.gif"; break; // Trooper
    }
    _type = type;
    _image = make_shared<ImageSFML>(_path);
}
client::Entities::~Entities() {}

<<<<<<< HEAD
void Entities::setId(int id) {_id = id;}
int Entities::getId(void) const {return _id;}
void Entities::setName(string name) {_name = name;}
string Entities::getName(void) const {return _name;}
size_t Entities::getEntityType(void) const {return (_type);};
shared_ptr<ImageSFML> Entities::getImage(void) const {return _image;}
=======
void client::Entities::setId(int id) {_id = id;}
int client::Entities::getId(void) const {return _id;}
void client::Entities::setName(string name) {_name = name;}
string client::Entities::getName(void) const {return _name;}
shared_ptr<client::ImageSFML> client::Entities::getImage(void) const {return _image;}
>>>>>>> 37db647d159404fdcecca9a2c2c5827e660b1c67
