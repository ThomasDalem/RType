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
#include "AComponents.hpp"
#include <iostream>

namespace game_engine
{
    class Render : public AComponents
    {
    public:
        Render(std::string ressourcePath_ct, Rectangle rect_ct)
            : ressourcePath(ressourcePath_ct), rect(rect_ct)
        {
            type = ComponentType::RENDER;
        }
        ~Render() {}
        std::string getRessourcePath() { return ressourcePath; }
        Rectangle getRect() { return rect; }

    private:
        std::string ressourcePath;
        Rectangle rect;
    };
} // namespace game_engine

#endif /* !RENDER_HPP_ */
