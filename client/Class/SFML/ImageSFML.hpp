/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Image SFML
*/

#ifndef __IMAGE__
#define __IMAGE__

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

using namespace std;
class ImageSFML {
    public:
        ImageSFML(string filepath);
        ~ImageSFML();

        void destroyTexture(void);
        string getPath(void) const;
        void setTexture(string filepath);
        void setScale(sf::Vector2f size);
        void setSprite(sf::Sprite newone);
        void setPosition(sf::Vector2f pos);
        shared_ptr<sf::Sprite> getSprite(void) const;

    private:
        string _path;
        shared_ptr<sf::Sprite> _sprite;
        shared_ptr<sf::Texture> _texture;
};

#endif
