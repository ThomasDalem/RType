#ifndef __WindowHandler__
#define __WindowHandler__

#include <vector>
#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "BackgroundSFML.hpp"

using namespace std;
class WindowHandler {
    public:
        WindowHandler(size_t width, size_t height, string name, size_t fps = 60);
        ~WindowHandler();

        //Setter
        void setTitle(string title);
        void setWidth(size_t width);
        void setHeight(size_t height);

        //Getter
        size_t getWidth(void) const;
        string getTitle(void) const;
        size_t getHeight(void) const;
        Background *getBackground(void) const;

        //Graphics Data
        void rmText(size_t row);
        void rmImage(size_t row);
        void addText(TextSfml news);
        void addImage(ImageSFML news);

        //Window data
        bool isOpen(void) const;
        void display(void) const;
        void setFramerate(size_t fps) const;

    private:
        string _title;
        size_t _width;
        size_t _height;
        Background *_background;

        vector<shared_ptr<TextSfml>> _texts;
        shared_ptr<sf::RenderWindow> _window;
        vector<shared_ptr<ImageSFML>> _images;

    protected:
};

#endif