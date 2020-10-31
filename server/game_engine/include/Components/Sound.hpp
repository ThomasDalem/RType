/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <iostream>

namespace game_engine {
    struct Sound
    {
        Sound(std::string ressourcePath_ct)
        : ressourcePath(ressourcePath_ct)
        {}

        std::string ressourcePath;
    };
}

#endif /* !SOUND_HPP_ */
