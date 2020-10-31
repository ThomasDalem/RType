#include <iostream>

#ifndef __VEntitie__
#define __VEntitie__

#include <memory>
#include <iostream>

#include "ImageSFML.hpp"

using namespace std;
enum Type {Monster, Player, Bullet, Obstacle};

class VEntitie {
    public:
        VEntitie();
        ~VEntitie();

    private:
        size_t id;
        Type _type;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif