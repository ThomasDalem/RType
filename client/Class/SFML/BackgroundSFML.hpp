/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Background
*/

#ifndef __BackgroundSFML__
#define __BackgroundSFML__

#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "ImageSFML.hpp"

using namespace std;
class Background {
    public:
        Background(int refresh = 1920);
        ~Background();

        void move(void);
        void stop(void) const;
        void speedUp(size_t sp = 1) const;
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        int _refresh;
        int _position;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif