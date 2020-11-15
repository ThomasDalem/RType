#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Client.hpp"
#include "Animation.hpp"
#include "Environment.hpp"
#include "WindowHandler.hpp"

using namespace std;
using namespace client;
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Animation
Test(Animation, clock, .init = redirect_all_std) {
    Animation _test;

    cr_assert(!_test.checkTimerAnimation());
    sleep(1);
    cr_assert(_test.checkTimerAnimation());
}

//Client
Test(Client, PlayerNumber, .init = redirect_all_std) {
    Client _client;

    cr_assert(_client.getNumbersPlayer() == 1);
}

//Environnement
Test(Environnement, Score, .init = redirect_all_std) {
    Environment env;

    cr_assert(env.getScore() == 0);
    env.setScore(19);
    cr_assert(env.getScore() == 19);
}

Test(Environnement, Health, .init = redirect_all_std) {
    Environment env;

    cr_assert(env.getHealth() == 0);
    env.setHealh(10);
    cr_assert(env.getHealth() == 10);
}

//MusicSystem
Test(MusicSystem, Musics, .init = redirect_all_std) {
    MusicSystem core;

    core.shot();
    core.dead();
    core.main();
    core.blowup();
}

//WindowHandler
Test(WindowHandler, Title, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    cr_assert(window.getTitle() == "unit_test");
    window.setTitle("Criterion Test Successfull");
    cr_assert(window.getTitle() == "Criterion Test Successfull");
}

Test(WindowHandler, Size, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    cr_assert(window.getWidth() == 1);
    window.setWidth(2);
    cr_assert(window.getWidth() == 2);
    cr_assert(window.getHeight() == 1);
    window.setHeight(2);
    cr_assert(window.getHeight() == 2);
}

Test(WindowHandler, Open, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    cr_assert(window.isOpen());
}

Test(WindowHandler, Texts, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    window.addText(make_shared<TextSfml>("Hello World !", "resources/fonts/2MASS.otf", sf::Color::White, 0, 0));
    window.rmText(0);
}

Test(WindowHandler, Images, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    window.addImage(make_shared<ImageSFML>("resources/sprites/r-typesheet10.gif"));
    window.rmImage(0);
}

Test(WindowHandler, Closer, .init = redirect_all_std) {
    WindowHandler window(1, 1, "unit_test");

    window.close();
}

// shared_ptr<Background> getBackground(void) const;
// shared_ptr<sf::RenderWindow> getWindow(void) const;
// void dispBackground();
// Input isEvent(Player &);
// void setFramerate(size_t) const;
// void dispEntities(vector<shared_ptr<Entities>> entities) const;
// void dispEnvironment(std::shared_ptr<client::Environment> &environment) const;
// void display() const;
