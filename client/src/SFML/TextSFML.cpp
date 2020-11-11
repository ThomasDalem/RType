/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Text SFML
*/

#include "TextSFML.hpp"

using namespace std;
client::TextSfml::TextSfml(string value, string font, sf::Color color, int x, int y) {
    _font = make_shared<sf::Font>();
    _data = make_shared<sf::Text>();
    _pos = make_shared<sf::Vector2f>(x, y);
    _TextColor = make_shared<sf::Color>(color);

    _font->loadFromFile(font);

    _data->setFont(*_font);
    _data->setCharacterSize(20);
    _data->setString(value.c_str());
    _data->setFillColor(*_TextColor);
    _data->setPosition(*_pos);
}
client::TextSfml::~TextSfml() {}

void client::TextSfml::setColor(sf::Color color) {
    _TextColor = make_shared<sf::Color>(color);
    _data->setFillColor(*_TextColor);
}

void client::TextSfml::update(string value, sf::Color color) {
    _TextColor = make_shared<sf::Color>(color);
    _data->setString(value.c_str());
    _data->setFillColor(*_TextColor);
}

void client::TextSfml::setPosition(sf::Vector2f pos) {
    _pos = make_shared<sf::Vector2f>(pos.x, pos.y);
    _data->setPosition(pos);
}

shared_ptr<sf::Text> client::TextSfml::getData(void) const {return _data;}
shared_ptr<sf::Font> client::TextSfml::getFont(void) const {return _font;}
void client::TextSfml::setSize(size_t size) {_data->setCharacterSize(size);}
shared_ptr<sf::Color> client::TextSfml::getColor(void) const {return _TextColor;}
shared_ptr<sf::Vector2f> client::TextSfml::getPosition(void) const {return _pos;}
void client::TextSfml::setString(string str = "Error") {_data->setString(str);}
