#ifndef __Mainmenu__
#define __Mainmenu__

#include <memory>
#include <iostream>

#include "Sfml.hpp"
#include "Button.hpp"
#include "Player.hpp"

using namespace std;
enum ReturnMain {Room, Creating, Quit};

class Mainmenu {
    public:
        Mainmenu();
        ~Mainmenu();

        void EventHandler(shared_ptr<sf::RenderWindow> _window);
        ReturnMain loop(shared_ptr<sf::RenderWindow> _window, Player &player);

    private:
        bool isHost;
        bool isJoin;
        string _name;
        shared_ptr<Button> _host;
        shared_ptr<Button> _join;

    protected:
};

#endif