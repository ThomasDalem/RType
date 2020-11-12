#include "MusicSystem.hpp"

using namespace client;
MusicSystem::MusicSystem() {
    _main.load("./resources/sounds/main.ogg");
    _shot.load("./resources/sounds/shot.ogg");
    _dead.load("./resources/sounds/Dead.ogg");
    _blowup.load("./resources/sounds/impact.ogg");

    _main.start();
}
MusicSystem::~MusicSystem() {}

void MusicSystem::main(void) {
    if (_main.isLoaded())
        _main.start();
}

void MusicSystem::shot(void) {
    if (_shot.isLoaded())
        _shot.start();
}

void MusicSystem::dead(void) {
    if (_dead.isLoaded())
        _dead.start();
}

void MusicSystem::blowup(void) {
    if (_blowup.isLoaded())
        _blowup.start();
}
