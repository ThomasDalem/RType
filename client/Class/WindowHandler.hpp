#ifndef __WindowHandler__
#define __WindowHandler__

#include <vector>
#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "ImageSFML.hpp"

using namespace std;
class WindowHandler {
    public:
        WindowHandler(size_t width, size_t height, string name, size_t fps = 60);
        ~WindowHandler();

        void setFramerate(size_t fps) const;

        void setTitle(string title);
        void setWidth(size_t width);
        void setHeight(size_t height);

        size_t getWidth(void) const;
        string getTitle(void) const;
        size_t getHeight(void) const;

        bool isOpen(void) const;
        void display(void) const;

    private:
        size_t _width;
        size_t _height;
        string _title;

        shared_ptr<sf::RenderWindow> _window;
        vector<shared_ptr<ImageSFML>> _images;

    protected:
};

#endif