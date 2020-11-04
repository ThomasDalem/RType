/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#ifndef __Player__
#define __Player__

#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

using namespace std;
class Player {
    public:
        Player();
        ~Player();

        void setName(string str);
        void setRoom(int room);
        int getRoom(void) const;
        string getName(void) const;
        void setHealth(size_t hlth);
        size_t getHealth(void) const;
        void setImage(ImageSFML news);
        sf::Vector2f getPosition(void) const;
        void setPosition(sf::Vector2f newpos);
        shared_ptr<ImageSFML> getImage(void) const;
        shared_ptr<TextSfml> getNameText(void) const;

    private:
        int _room;
        string _name;
        size_t _health;
        sf::Vector2f _pos;
        shared_ptr<ImageSFML> _image;
        shared_ptr<TextSfml> _textname;

    protected:
};

#endif
