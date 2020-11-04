/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Trooper
*/

#include "Trooper.hpp"

enemies::Trooper::Trooper()
{
}

enemies::Trooper::~Trooper()
{
}

extern "C" enemies::Trooper *entryPoint()
{
    return (new enemies::Trooper());
}