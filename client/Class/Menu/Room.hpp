#ifndef __RoomMenu__
#define __RoomMenu__

#include <memory>
#include <vector>
#include <iostream>

#include "Sfml.hpp"
#include "Button.hpp"

using namespace std;
class RoomMenu {
    public:
        RoomMenu(string name = "");
        ~RoomMenu();

        string loop(shared_ptr<sf::RenderWindow> _window);
        void EventHandler(shared_ptr<sf::RenderWindow> _window);

    private:
        bool isMenu;
        string _name;
        vector<shared_ptr<Button>> roomlist;

    protected:
};

#endif