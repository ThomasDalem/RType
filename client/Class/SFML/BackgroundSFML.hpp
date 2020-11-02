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
        Background(int refresh = 0);
        ~Background();

        void move(void);
        void stop(void) const;
        void speedUp(int sp = 0);
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        int _refresh;
        int _position;
        bool _movement;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif