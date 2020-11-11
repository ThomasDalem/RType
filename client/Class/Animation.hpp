/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include "Entities.hpp"

namespace client {
    class Animation {
        public:
            Animation();
            ~Animation();
            bool checkTimerAnimation();
            void updateAnimation(vector<shared_ptr<Entities>> &entities);
            void updateImageRect(shared_ptr<Entities> &entitie, int max_left, int min_left);

        protected:
        private:
            sf::Clock _clock;
    };
}

#endif /* !ANIMATION_HPP_ */
