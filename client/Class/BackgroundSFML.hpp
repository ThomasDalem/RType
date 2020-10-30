#ifndef __BackgroundSFML__
#define __BackgroundSFML__

#include <memory>
#include <iostream>

#include "ImageSFML.hpp"

using namespace std;
class Background {
    public:
        Background();
        ~Background();

        void stop(void) const;
        void move(void) const;
        void speedUp(size_t sp = 1) const;
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif