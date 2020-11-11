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

using namespace std;
enum ReturnRoom {Continue, Salle, Back};

class RoomMenu {
    public:
        RoomMenu(string = "", size_t = 0);
        ~RoomMenu();

        void addItems(vector<shared_ptr<Button>> &, size_t);
        ReturnRoom loop(shared_ptr<sf::RenderWindow>, Player &);
        void EventHandler(shared_ptr<sf::RenderWindow>, Player &);
        ReturnRoom creatingGame(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Player>> players);

    private:
        bool isMenu;
        bool isPlay;
        string _name;
        shared_ptr<Button> _play;
        vector<shared_ptr<Button>> roomlist;

    protected:
};

#endif