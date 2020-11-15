/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Environment
*/

#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <iostream>
#include <memory>

#include "Sfml.hpp"
#include "Player.hpp"
#include "TextSFML.hpp"
#include "Entities.hpp"
#include "ImageSFML.hpp"
#include "BackgroundSFML.hpp"

namespace client {
    class Environment {
        public:
            Environment();
            ~Environment();

            int getScore() const;
            void setScore(int score);
            void incScore();
            int getHealth() const;
            void setHealh(int _health);
            std::shared_ptr<ImageSFML> getPlayerSprite() const;
            std::shared_ptr<TextSfml> getScoreText() const;
            std::shared_ptr<TextSfml> getHealthText() const;
            std::shared_ptr<TextSfml> getPlayerName() const;
            void setPlayerRectangle(sf::IntRect rect);
            void setScoreText(int score);
            void setHealthText(int health);
            void setPlayerName(std::string name);

        private:
            int _score;
            int _health;
            std::shared_ptr<ImageSFML> _playerSprite;
            std::shared_ptr<TextSfml> _scoreText;
            std::shared_ptr<TextSfml> _healthText;
            std::shared_ptr<TextSfml> _playerName;
        protected:
    };
} // namespace client

#endif /* !ENVIRONMENT_HPP_ */
