#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "ManetteSFML.hpp"

using namespace std;
using namespace client;
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Manette(s)
Test(Manette, Connection, .init = redirect_all_std) {
    ManetteSFML Remote;

    if (Remote.isConnected()) {
        cr_assert(Remote.howManyConnected() > 0);
    } else {
        cr_assert(Remote.howManyConnected() == 0);
    }
}

Test(Manette, ButtonClicked_1, .init = redirect_all_std) {
    ManetteSFML Remote;

    if (Remote.isConnected()) {
        cr_assert(Remote.getButtonsClicked() == ManetteSFML::Nada);
    } else {
        cr_assert(Remote.howManyConnected() == 0);
    }
}

Test(Manette, ButtonClicked_2, .init = redirect_all_std) {
    ManetteSFML Remote;

    if (Remote.isConnected()) {
        cr_assert(!Remote.isClicked(ManetteSFML::Nada));
    } else {
        cr_assert(Remote.howManyConnected() == 0);
    }
}

Test(Manette, Sensibility, .init = redirect_all_std) {
    ManetteSFML Remote;

    Remote.setSensibility(50);
    cr_assert(Remote.getSensibility() == 50);
}

Test(Manette, Joysticks_1, .init = redirect_all_std) {
    ManetteSFML Remote;

    if (Remote.isConnected()) {
        cr_assert(Remote.getAxis().x < 50 && Remote.getAxis().y < 50);
    } else {
        cr_assert(Remote.howManyConnected() == 0);
    }
}

Test(Manette, Joysticks_2, .init = redirect_all_std) {
    ManetteSFML Remote;

    if (Remote.isConnected()) {
        cr_assert(Remote.getJoysDirection() == ManetteSFML::Direction::Nothing);
    } else {
        cr_assert(Remote.howManyConnected() == 0);
    }
}

//Image(s)
Test(Image, Variables_1, .init = redirect_all_std) {
    ImageSFML image("./resources/sprites/r-typesheet10.gif");

    cr_assert(image.getPath() == "./resources/sprites/r-typesheet10.gif");
}

Test(Image, Texture, .init = redirect_all_std) {
    ImageSFML image("./resources/sprites/r-typesheet10.gif");

    image.setTexture("./resources/sprites/block.png");
}

Test(Image, Rotation, .init = redirect_all_std) {
    ImageSFML image("./resources/sprites/r-typesheet10.gif");

    image.setRotate(90);
    image.setRotate(180);
    image.setRotate(270);
    image.setRotate(360);
    image.setRotate(-90);
    image.setRotate(-180);
    image.setRotate(-270);
    image.setRotate(-360);
}

Test(Image, Scale, .init = redirect_all_std) {
    ImageSFML image("./resources/sprites/r-typesheet10.gif");

    image.setScale(sf::Vector2f(0, 0));
    image.setScale(sf::Vector2f(0, 2));
    image.setScale(sf::Vector2f(0, -2));
    image.setScale(sf::Vector2f(2, 0));
    image.setScale(sf::Vector2f(2, 2));
    image.setScale(sf::Vector2f(2, -2));
    image.setScale(sf::Vector2f(-2, 0));
    image.setScale(sf::Vector2f(-2, 2));
    image.setScale(sf::Vector2f(-2, -2));
}

Test(Image, Position, .init = redirect_all_std) {
    ImageSFML image("./resources/sprites/r-typesheet10.gif");

    image.setPosition(sf::Vector2f(0, 0));
    image.setPosition(sf::Vector2f(0, 2));
    image.setPosition(sf::Vector2f(0, -2));
    image.setPosition(sf::Vector2f(2, 0));
    image.setPosition(sf::Vector2f(2, 2));
    image.setPosition(sf::Vector2f(2, -2));
    image.setPosition(sf::Vector2f(-2, 0));
    image.setPosition(sf::Vector2f(-2, 2));
    image.setPosition(sf::Vector2f(-2, -2));
}

//Text(s)
Test(Text, Size, .init = redirect_all_std) {
    TextSfml text("Hello World !", "resources/fonts/2MASS.otf", sf::Color::White, 0, 0);

    text.setSize(0);
    text.setSize(10);
    text.setSize(50);
    text.setSize(100);
    text.setSize(250);
}

Test(Text, String, .init = redirect_all_std) {
    TextSfml text("Hello World !", "resources/fonts/2MASS.otf", sf::Color::White, 0, 0);

    text.setString("Hello My World !");
    cr_assert(text.getData()->getString() == "Hello My World !");
}

Test(Text, Position, .init = redirect_all_std) {
    TextSfml text("Hello World !", "resources/fonts/2MASS.otf", sf::Color::White, 0, 0);

    text.setPosition(sf::Vector2f(0, 0));
    text.setPosition(sf::Vector2f(0, 2));
    text.setPosition(sf::Vector2f(0, -2));
    text.setPosition(sf::Vector2f(2, 0));
    text.setPosition(sf::Vector2f(2, 2));
    text.setPosition(sf::Vector2f(2, -2));
    text.setPosition(sf::Vector2f(-2, 0));
    text.setPosition(sf::Vector2f(-2, 2));
    text.setPosition(sf::Vector2f(-2, -2));
    cr_assert(text.getPosition()->x == -2 && text.getPosition()->y == -2);
}
