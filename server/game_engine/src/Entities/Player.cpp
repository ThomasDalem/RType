/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#include "Player.hpp"

game_engine::Player::Player(Vector _position, PlayerColor playerColor, int clientID, boost::asio::ip::udp::endpoint endpoint)
{
    _uniqueID = clientID;
    _clientID = clientID;
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _health = std::make_shared<Health>(10000, true);
    _collision = std::make_shared<Collision>(Rectangle(_position.x, _position.y, 96, 48), false);
    if (playerColor == PlayerColor::Blue)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 2, 33, 16));
    if (playerColor == PlayerColor::Yellow)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 20, 33, 16));
    if (playerColor == PlayerColor::Red)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 53, 33, 16));
    if (playerColor == PlayerColor::Green)
        _render = std::make_shared<Render>("./path_to_player sprite", Rectangle(0, 36, 33, 16));

    _deathSound = std::make_shared<Sound>("./path_to_death_sound");
    _entitesID = EntitiesType::PLAYER;
    _timeInvincibility = 0;
    _speedMultiplicator = 1.35;
    _score = 0;
    _endpoint = endpoint;
    _componentList.push_back(_transform);
    _componentList.push_back(_deathSound);
    _componentList.push_back(_health);
    _componentList.push_back(_collision);
    _componentList.push_back(_render);
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