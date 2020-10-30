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