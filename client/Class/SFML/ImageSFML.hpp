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

namespace client {
    class ImageSFML {
        public:
            ImageSFML(string filepath);
            ~ImageSFML();

            void setRotate(int);
            void setTexture(string);
            void destroyTexture(void);
            string getPath(void) const;
            void setSprite(sf::Sprite);
            void setScale(sf::Vector2f);
            void setPosition(sf::Vector2f);
            void setRectangleSheep(sf::IntRect);
            sf::IntRect getRectangleSheep() const;
            shared_ptr<sf::Sprite> getSprite(void) const;
            int isClicked(sf::Event, shared_ptr<sf::RenderWindow>);

        private:
            string _path;
            shared_ptr<sf::Sprite> _sprite;
            shared_ptr<sf::Texture> _texture;
    };
}

#endif
