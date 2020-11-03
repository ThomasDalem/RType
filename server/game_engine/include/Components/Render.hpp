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
        Render(std::string ressourcePath, Rectangle rect)
            : AComponents(ComponentType::RENDER), _ressourcePath(ressourcePath), _rect(rect)
        {
            _type = ComponentType::RENDER;
        }
        ~Render() {}
        std::string getRessourcePath() const { return _ressourcePath; }
        Rectangle getRect() const { return _rect; }

    private:
        std::string _ressourcePath;
        Rectangle _rect;
    };
} // namespace game_engine

#endif /* !RENDER_HPP_ */
