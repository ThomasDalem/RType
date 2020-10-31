/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Monster
*/

#ifndef __Monster__
#define __Monster__

#include <memory>
#include <iostream>

#include "VMonster.hpp"
#include "ImageSFML.hpp"

using namespace std;
class Monster : VMonster {
    public:
        Monster();
        ~Monster();

        bool operator=(Monster another);
        bool operator==(Monster another);

        void shoot(void);

    private:
        size_t id;
        size_t health;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif