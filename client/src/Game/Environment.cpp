/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Environment
*/

#include "Environment.hpp"

client::Environment::Environment()
{
    _score = 0;
    _health = 0;
    _playerSprite = make_shared<ImageSFML>("./resources/sprites/r-typesheet42.gif");
    _scoreText = make_shared<TextSfml>("score: 0", "./resources/fonts/2MASS.otf", sf::Color::White, 820, 920);
    _healthText = make_shared<TextSfml>("health: 0", "./resources/fonts/2MASS.otf", sf::Color::White, 820, 960);
    _playerSprite->setScale(sf::Vector2f(2, 2));
    _playerSprite->setPosition(sf::Vector2f(980, 960));
}

client::Environment::~Environment()
{
}

int client::Environment::getScore() const
{
    return (_score);
}

void client::Environment::setScore(int score)
{
    _score = score;
}

void client::Environment::incScore()
{
    _score++;
}

int client::Environment::getHealth() const
{
    return (_health);
}

void client::Environment::setHealh(int health)
{
    _health = health;
}

std::shared_ptr<client::ImageSFML> client::Environment::getPlayerSprite() const
{
    return (_playerSprite);
}

std::shared_ptr<client::TextSfml> client::Environment::getScoreText() const
{
    return (_scoreText);
}

std::shared_ptr<client::TextSfml> client::Environment::getHealthText() const
{
    return (_healthText);
}

void client::Environment::setPlayerRectangle(sf::IntRect rect)
{
    _playerSprite->setRectangleSheep(rect);
}
void client::Environment::setScoreText(int score)
{
    _scoreText->update("score: " + to_string(score), sf::Color::White);
}

void client::Environment::setHealthText(int health)
{
    _scoreText->update("health: " + to_string(health), sf::Color::White);
}
