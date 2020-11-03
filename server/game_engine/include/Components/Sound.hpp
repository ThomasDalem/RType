/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <iostream>
#include "AComponents.hpp"

namespace game_engine
{
    class Sound : public AComponents
    {
    public:
        Sound(std::string ressourcePath)
            : AComponents(ComponentType::SOUND), _ressourcePath(ressourcePath)
        {
            _type = ComponentType::SOUND;
        }
        ~Sound() {}
        std::string getRessourcePath() {return _ressourcePath;}

    private:
        std::string _ressourcePath;
    };
} // namespace game_engine

#endif /* !SOUND_HPP_ */
