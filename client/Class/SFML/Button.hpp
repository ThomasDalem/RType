/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** ButtonSFML
*/

#ifndef __Button__
#define __Button__

#include <memory>
#include <iostream>

#include "Sfml.hpp"

using namespace std;
class Button {
    public:
        Button(sf::Vector2f pos, sf::Vector2f size);
        ~Button();

        void drawButton(shared_ptr<sf::RenderWindow> window);
        int isClicked(sf::Event event, shared_ptr<sf::RenderWindow> window);
        void setColor(sf::Color buttonColor, sf::Color boundColor, float boundSize);
        void setText(string fontPath, string Text, int size, const sf::Color textColor);

    private:
        sf::Font font;
        sf::Text text;
        int is_clicked;
        int is_hovered;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Color buttonColor;
        sf::RectangleShape button;

    protected:
};

#endif
