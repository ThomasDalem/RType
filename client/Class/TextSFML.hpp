#ifndef _TEXTSFML_
#define _TEXTSFML_

#include <SFML/Graphics.hpp>

class TextSfml {
    public:
        TextSfml(std::string value, std::string font, sf::Color color, int x, int y);
        ~TextSfml();
        void setString(std::string str);
        void setColor(sf::Color color);
        void update(std::string value, sf::Color color);

        sf::Text _data;
        sf::Font _font;
        sf::Color _TextColor;
};

#endif