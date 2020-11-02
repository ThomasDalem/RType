/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Text SFML
*/

#ifndef _TEXTSFML_
#define _TEXTSFML_

#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
class TextSfml {
    public:
        TextSfml(string value, string font, sf::Color color = sf::Color::White, int x = 0, int y = 0);
        ~TextSfml();

        void setSize(size_t size);
        void setString(string str);
        void setPosition(sf::Vector2f pos);
        void setColor(sf::Color color = sf::Color::White);
        void update(string value, sf::Color color = sf::Color::White);
        shared_ptr<sf::Text> getData(void) const;
        shared_ptr<sf::Font> getFont(void) const;
        shared_ptr<sf::Color> getColor(void) const;
        shared_ptr<sf::Vector2f> getPosition(void) const;

    private:
        shared_ptr<sf::Text> _data;
        shared_ptr<sf::Font> _font;
        shared_ptr<sf::Vector2f> _pos;
        shared_ptr<sf::Color> _TextColor;

    protected:
};

#endif