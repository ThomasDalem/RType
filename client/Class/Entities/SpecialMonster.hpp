/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Monster
*/

#ifndef __SpecialMonster__
#define __SpecialMonster__

#include <memory>
#include <iostream>

#include "VMonster.hpp"
#include "ImageSFML.hpp"

using namespace std;
class SMonster : VMonster {
    public:
        SMonster();
        ~SMonster();

        bool operator=(SMonster another);
        bool operator==(SMonster another);

        void shoot(void);

    private:
        size_t id;
        size_t health;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif