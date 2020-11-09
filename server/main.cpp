/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** main
*/

#include <dlfcn.h>
#include <stdio.h>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <cstdio>
#include <ctime>
#include <dirent.h>

#include "Vector.hpp"

#include "DDLoader.hpp"
#include "Enemy.hpp"

int main()
{
    DDloader<game_engine::Enemy> ennemyLoader;
    DIR *pDIR;
    std::vector<std::string> ennemyLib;
    std::string file;
    struct dirent *entry;
    //int ennemySelected;

    pDIR = opendir("./lib");
    if (pDIR == nullptr)
        throw (Exception("Can't find ennemy directory"));
    while (entry = readdir(pDIR)) {
        file.assign(entry->d_name);
        if (file.find(".so") != std::string::npos) {
            file.insert(0, "./lib");
            ennemyLib.push_back(file);
            std::cout << file.c_str() << std::endl;
            std::shared_ptr<game_engine::Enemy> enemy = ennemyLoader.getInstance(file.c_str(), game_engine::Vector(0, 0));
            enemy->pathEnemy();
        }
    }
    closedir(pDIR);
    if (ennemyLib.size() == 0)
        throw (Exception("No library found in ennemy directory"));
    // ennemySelected = rand() % ennemyLib.size();
    // ennemyLoader.loadLibrary(ennemyLib[ennemySelected].c_str());
    return (0);
}