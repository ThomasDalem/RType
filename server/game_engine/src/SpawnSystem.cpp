/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SpawnSystem
*/

#include "SpawnSystem.hpp"

game_engine::SpawnSystem::SpawnSystem(std::vector<std::shared_ptr<IEntities>> &entities): _entities(entities)
{
}

game_engine::SpawnSystem::~SpawnSystem()
{
}

void game_engine::SpawnSystem::loadEnemyLibrary()
{

}

void game_engine::SpawnSystem::spawnEnemy()
{
    // DDloader<Enemy> ennemyLoader;
    // DIR *pDIR;
    // std::vector<std::string> ennemyLib;
    // std::string file;
    // struct dirent *entry;
    // int ennemySelected;

    // pDIR = opendir("./ennemyLib");
    // if (pDIR == nullptr)
    //     throw (Exception("Can't find ennemy directory"));
    // while (entry = readdir(pDIR)) {
    //     file.assign(entry->d_name);
    //     if (file.find(".so") != std::string::npos) {
    //         file.insert(0, "./ennemyLib/");
    //         ennemyLib.push_back(file);
    //     }
    // }
    // closedir(pDIR);
    // if (ennemyLib.size() == 0)
    //     throw (Exception("No library found in ennemy directory"));
    // ennemySelected = rand() % ennemyLib.size();
    // ennemyLoader.loadLibrary(ennemyLib[ennemySelected].c_str());
}

void game_engine::SpawnSystem::newPlayer(int clientID)
{
    std::shared_ptr<Player> newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Green, clientID);
}