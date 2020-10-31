/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include "../EntitiesEnum.hpp"
#include "../Rectangle.hpp"

#include <iostream>

namespace game_engine {
    struct Render
    {
        Render(std::string ressourcePath_ct, Rectangle rect_ct)
        : ressourcePath(ressourcePath_ct), rect(rect_ct)
        {}

        std::string ressourcePath;
        Rectangle rect;
    };
}

#endif /* !RENDER_HPP_ */
