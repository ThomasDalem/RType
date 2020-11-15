/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** main
*/

#include <iostream>
#include "Exception.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./r-type_server [TCP port] [UDP port]" << std::endl;
        return 1;
    }
    try {
        Server server(std::atoi(av[1]), std::atoi(av[2]));
        server.mainLoop();
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