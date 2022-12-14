/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Window Handker
*/

#ifndef __WindowHandler__
#define __WindowHandler__

#include <vector>
#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "Player.hpp"
#include "TextSFML.hpp"
#include "Entities.hpp"
#include "ImageSFML.hpp"
#include "BackgroundSFML.hpp"
#include "Environment.hpp"

using namespace std;

namespace client {
    enum Input {
        Left,
        Right,
        Up,
        Down,

        LeftUp,
        RightUp,
        LeftDown,
        RightDown,

        Shoot,

        Nothing,
        Escape
    };

    class WindowHandler {
        public:
            WindowHandler(size_t, size_t, string, size_t = 60);
            ~WindowHandler();

            //Setter
            void setTitle(string);
            void setWidth(size_t);
            void setHeight(size_t);

            //Getter
            size_t getWidth(void) const;
            string getTitle(void) const;
            size_t getHeight(void) const;
            shared_ptr<Background> getBackground(void) const;
            shared_ptr<sf::RenderWindow> getWindow(void) const;
            void dispBackground();

            //Graphics Data
            void rmText(size_t);
            void rmImage(size_t);
            void addText(shared_ptr<TextSfml>);
            void addImage(shared_ptr<ImageSFML>);

            //Window data
            bool isOpen(void) const;
            Input isEvent(Player &);
            void setFramerate(size_t) const;
            void dispEntities(vector<shared_ptr<Entities>> entities) const;
            void dispEnvironment(std::shared_ptr<client::Environment> &environment) const;
            void display() const;
            void close();

        private:
            string _title;
            size_t _width;
            size_t _height;

            shared_ptr<Background> _background;
            vector<shared_ptr<TextSfml>> _texts;
            shared_ptr<sf::RenderWindow> _window;
            vector<shared_ptr<ImageSFML>> _images;

        protected:
    };
}

#endif