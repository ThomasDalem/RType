/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Environment
*/

#include "Environment.hpp"

game_engine::Environment::Environment(Vector _position)
{
    //le rectangle, les path et la rotation sont à changer avec les vraies valeur
    _transform = std::make_shared<Transform>(_position, 0, Vector(0, 0));
    _render = std::make_shared<Render>("./path_to_background", Rectangle(0, 0, 75, 45));
    _music = std::make_shared<Sound>("./path_to_music");
    _entitesID = EntitiesType::ENVIRONNEMENT;
    _componentList.push_back(_transform);
    _componentList.push_back(_render);
    _componentList.push_back(_music);
}
