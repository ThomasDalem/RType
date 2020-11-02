#ifndef __Mainmenu__
#define __Mainmenu__

#include <memory>
#include <iostream>

#include "Sfml.hpp"

using namespace std;
class Mainmenu {
    public:
        Mainmenu();
        ~Mainmenu();

        string loop(shared_ptr<sf::RenderWindow> _window);
        void EventHandler(shared_ptr<sf::RenderWindow> _window);

    private:
        bool isMenu;
        string _name;

    protected:
};

#endif