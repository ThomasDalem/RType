/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Image SFML
*/

#include <iostream>
#include "ImageSFML.hpp"

using namespace std;

ImageSFML::ImageSFML(string path)
{
    _texture = new sf::Texture;

    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
}

void ImageSFML::setTexture(string path)
{
    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
}