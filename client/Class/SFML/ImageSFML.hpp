/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Image SFML
*/

#ifndef __IMAGE__
#define __IMAGE__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
class ImageSFML {
    public:
        ImageSFML(string filepath);
        ~ImageSFML() {}

        void destroyTexture();
        string getPath() const;
        void setTexture(string filepath);
        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        sf::Sprite getSprite() const { return (_sprite); }

    private:
        string _path;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif
