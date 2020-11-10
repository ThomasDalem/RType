/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

game_engine::Player::Player(Vector _position, PlayerColor playerColor, int clientID)
{
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _uniqueID = clientID;
    _clientID = clientID;
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _health = std::make_shared<Health>(1, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 32, 16), false);
    if (playerColor == PlayerColor::Blue)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(2, 2, 32, 16));
    if (playerColor == PlayerColor::Yellow)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(2, 20, 32, 16));
    if (playerColor == PlayerColor::Red)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(2, 36, 32, 16));
    if (playerColor == PlayerColor::Green)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(2, 53, 32, 16));

    _deathSound = std::make_shared<Sound>("./path_to_death_sound");
    _entitesID = EntitiesType::PLAYER;
    _timeInvincibility = 0;
    _speedMultiplicator = 1;
    _score = 0;
}

void game_engine::Player::addNewInput(network::Event event, int value[10])
{
    int moveX = 0;
    int moveY = 0;

    if (event == network::Event::MOVE) {
        moveX = value[0];
        moveY = value[1];
        if (moveX > 0 && moveY == 0)
            inputBuffer.push_back(InputEnum::MOVELEFT);
        if (moveX < 0 && moveY == 0)
            inputBuffer.push_back(InputEnum::MOVERIGHT);
        if (moveX == 0 && moveY > 0)
            inputBuffer.push_back(InputEnum::MOVEDOWN);
        if (moveX == 0 && moveY < 0)
            inputBuffer.push_back(InputEnum::MOVEUP);
    }
    if (event == network::Event::SHOOT)
        inputBuffer.push_back(InputEnum::SHOOTINPUT);
}