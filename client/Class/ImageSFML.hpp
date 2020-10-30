#ifndef __IMAGE__
#define __IMAGE__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
class ImageSFML {
    public:
        ImageSFML(string filepath);
        ~ImageSFML() {}

        void destroyTexture();
        void setTexture(string filepath);
        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        sf::Sprite getSprite() const { return (_sprite); }

    private:
        sf::Texture *_texture;
        sf::Sprite _sprite;
};

#endif
