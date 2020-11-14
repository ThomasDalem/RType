/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** ButtonSFML
*/

#include "Button.hpp"

client::Button::Button(sf::Vector2f _pos, sf::Vector2f _size): pos(_pos), size(_size) {
    _sound.load("./resources/sounds/menu.ogg");

    isOn = false;

    button.setPosition(_pos);
    button.setSize(_size);
}
client::Button::~Button() {}

void client::Button::setText(string fontPath, string _text, int _size, const sf::Color textColor) {
    sf::Vector2f textPos;

    if (!font.loadFromFile(fontPath))
        cout << "can't load button text font \n" << endl;
    text.setFont(font);
    text.setString(_text);
    text.setCharacterSize(_size);
    textPos.x = pos.x + (button.getSize().x / 2) - ((_text.length() / 2) * 50);
    textPos.y = pos.y + 5;
    text.setPosition(textPos);
    text.setFillColor(textColor);
}

void client::Button::setColor(sf::Color buttonColor, sf::Color boundColor, float boundSize) {
    button.setFillColor(buttonColor);
    button.setOutlineThickness(boundSize);
    button.setOutlineColor(boundColor);
}

void client::Button::drawButton(shared_ptr<sf::RenderWindow> window) {
    sf::Vector2i cursorPos = sf::Mouse::getPosition();
    sf::Vector2i windowPos = window->getPosition();

    if (button.getGlobalBounds().contains(sf::Vector2f(cursorPos.x - windowPos.x, cursorPos.y - windowPos.y))) {
        button.setOutlineColor(sf::Color::White);
        button.setFillColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
        if (!isOn)
            _sound.start();
        isOn = true;
    } else {
        isOn = false;
        _sound.reload();
        button.setOutlineColor(sf::Color::Black);
        button.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
    }
    window->draw(button);
    window->draw(text);
}

int client::Button::isClicked(sf::Event event, shared_ptr<sf::RenderWindow> window) {
    sf::Vector2i cursorPos;
    sf::Vector2i windowPos = window->getPosition();

    if (event.type == sf::Event::MouseButtonPressed) {
        cursorPos = sf::Mouse::getPosition();
        if (button.getGlobalBounds().contains(sf::Vector2f(cursorPos.x - windowPos.x, cursorPos.y - windowPos.y)))
            return true;
    }
    return false;
}