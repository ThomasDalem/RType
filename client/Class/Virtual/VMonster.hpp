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

#include "VEntity.hpp"
#include "ImageSFML.hpp"

using namespace std;
class VMonster : VEntitie {
    public:
        VMonster();
        ~VMonster();

        void operator=(VMonster another);
        bool operator==(VMonster another);

        void shoot(void);

    private:
        // size_t id;
        size_t health;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif