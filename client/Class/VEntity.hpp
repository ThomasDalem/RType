#include <iostream>

#ifndef __VEntitie__
#define __VEntitie__

#include <memory>
#include <iostream>

#include "ImageSFML.hpp"

using namespace std;
class VEntitie {
    public:
        VEntitie();
        ~VEntitie();

    private:
        size_t id;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif