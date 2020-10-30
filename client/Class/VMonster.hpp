/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Virtual Monster
*/

#ifndef __VirtualMonster__
#define __VirtualMonster__

#include <memory>
#include <iostream>

#include "ImageSFML.hpp"

using namespace std;
class VMonster {
    public:
        VMonster();
        ~VMonster();

        bool operator=(VMonster another);
        bool operator==(VMonster another);

        void shoot(void);

    private:
        size_t health;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif