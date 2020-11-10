/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client Entities
*/

#ifndef __Entities__
#define __Entities__

#include <memory>
#include <vector>

#include "ImageSFML.hpp"

using namespace std;
class Entities {
    public:
        Entities(int, size_t);
        ~Entities();

        void setId(int);
        int getId(void) const;
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        int _id;
        size_t type;
        string _path;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif