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
        Player(int32_t id);
        ~Player();

        void setId(int id);
        void setRoom(int room);
        int getRoom(void) const;
        int getId(void) const;
        void setName(string str);
        bool getAdmin(void) const;
        string getName(void) const;
        void setAdmin(bool boolean);
        void setImage(ImageSFML news);
        void setPosition(sf::Vector2f newpos);
        shared_ptr<ImageSFML> getImage(void) const;
        shared_ptr<TextSfml> getNameText(void) const;

    private:
        int _id;
        int _room;
        string _name;
        bool isAdmin;

        shared_ptr<ImageSFML> _image;
        shared_ptr<TextSfml> _textname;

    protected:
};

#endif
