/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Room Menu
*/

#ifndef __RoomMenu__
#define __RoomMenu__

#include <memory>
#include <vector>
#include <iostream>

#include "Sfml.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Button.hpp"

using namespace std;
enum ReturnRoom {Continue, Salle, Back};

class RoomMenu {
    public:
        RoomMenu(string = "", size_t = 0);
        ~RoomMenu();

        ReturnRoom loop(shared_ptr<sf::RenderWindow>, Player &);
        void EventHandler(shared_ptr<sf::RenderWindow>, Player &);
        void addItems(vector<shared_ptr<Button>> &roomlist, size_t row);
        ReturnRoom creatingGame(shared_ptr<sf::RenderWindow>, Player &);

    private:
        bool isMenu;
        bool isPlay;
        string _name;
        shared_ptr<Button> _play;
        vector<shared_ptr<Button>> roomlist;

    protected:
};

#endif