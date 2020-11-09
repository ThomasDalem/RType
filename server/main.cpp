/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** main
*/

#include "../game_engine/include/GameLoop.hpp"

int main()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> entities;
    std::shared_ptr<game_engine::GameLoop>gameLoop;

    try {
        entities = std::make_shared<std::vector<std::shared_ptr<game_engine::IEntities>>>();
        gameLoop = std::make_shared<game_engine::GameLoop>(entities);
        gameLoop->gameLoop();
    }
    catch (std::bad_alloc const &bad)
    {
        std::cerr << bad.what() << std::endl;
        return (84);
    }
    catch (Exception const &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}