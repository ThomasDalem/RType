/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Alien
*/

#include "Alien.hpp"

enemies::Alien::Alien()
{
}

enemies::Alien::~Alien()
{
}

extern "C" enemies::Alien *entryPoint()
{
    return (new enemies::Alien());
}