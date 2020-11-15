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

// shared_ptr<Background> getBackground(void) const;
// shared_ptr<sf::RenderWindow> getWindow(void) const;
// void dispBackground();
// void rmText(size_t);
// void rmImage(size_t);
// void addText(shared_ptr<TextSfml>);
// void addImage(shared_ptr<ImageSFML>);
// Input isEvent(Player &);
// void setFramerate(size_t) const;
// void dispEntities(vector<shared_ptr<Entities>> entities) const;
// void dispEnvironment(std::shared_ptr<client::Environment> &environment) const;
// void display() const;
// void close();