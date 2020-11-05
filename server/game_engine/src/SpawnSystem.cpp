/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SpawnSystem
*/

#include "SpawnSystem.hpp"

game_engine::SpawnSystem::SpawnSystem(std::vector<std::shared_ptr<IEntities>> &entities): _entities(entities)
{
    blockSpawnClock = std::clock();
    blockSpawnClock = 0.5;
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
    _entities.push_back(newPlayer);
}

void game_engine::SpawnSystem::spawnObstacle()
{
    double timePassed = clock() - blockSpawnClock;
    int obstacleChancetoSpawn;
    int nbObstacletoSpawn;
    int upOrDownSpawn;
    int upStart = 50;
    int downStart = 1040;

    if (timePassed > blockSpawnTime) {
        blockSpawnClock = clock();
        _entities.push_back(std::make_shared<StageObstacle>(Vector(0, 1920)));
        _entities.push_back(std::make_shared<StageObstacle>(Vector(1030, 1920)));
        addObstacle();
    }
}

void game_engine::SpawnSystem::addObstacle()
{
    int obstacleChancetoSpawn;
    int nbObstacletoSpawn;
    int upOrDownSpawn;
    int upStart = 50;
    int downStart = 1040;
    int stageObstacleOrNot;

    obstacleChancetoSpawn = rand() % 10;
    if (obstacleChancetoSpawn == 1) {
        nbObstacletoSpawn = rand() % 4;
        upOrDownSpawn = rand() % 2;
        if (upOrDownSpawn == 0) {
            for (upStart = 50; upStart <= nbObstacletoSpawn * 50; upStart+=50) {
                stageObstacleOrNot = rand() % 2;
                if (stageObstacleOrNot == 0)
                    _entities.push_back(std::make_shared<StageObstacle>(Vector(upStart, 1920)));
                else
                    _entities.push_back(std::make_shared<DestroyableTile>(Vector(upStart, 1920)));
            }
        }
        else {
            for (downStart = 1040; downStart <= 1040 - 50 * nbObstacletoSpawn; downStart-=50) {
                stageObstacleOrNot = rand() % 2;
                if (stageObstacleOrNot == 0)
                    _entities.push_back(std::make_shared<StageObstacle>(Vector(downStart, 1920)));
                else
                    _entities.push_back(std::make_shared<DestroyableTile>(Vector(downStart, 1920)));
            }
        }
    }
}

void game_engine::SpawnSystem::checkEntitieShoot()
{
    std::vector<std::shared_ptr<game_engine::IEntities>> newListPlayer;
    std::vector<std::shared_ptr<game_engine::IEntities>> newListEnnemy;

    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities, newListPlayer);
    EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMY}, _entities, newListEnnemy);
    checkPlayerShoot(newListPlayer);
    checkEnnemyShoot(newListEnnemy, newListPlayer);
}

void game_engine::SpawnSystem::checkPlayerShoot(std::vector<std::shared_ptr<game_engine::IEntities>> newListPlayer)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    game_engine::Player *player;
    int bulletPosX = 0;
    int bulletPosY = 0;

    for (listPlayerIter = newListPlayer.begin(); listPlayerIter != newListPlayer.end(); listPlayerIter++) {
        player = static_cast<Player *>(listPlayerIter->get());
        if (player->getFirstEnum() == InputEnum::SHOOTINPUT) {
            bulletPosX = player->getTransform()->getPosition().x + player->getCollision()->getRectSize().L;
            bulletPosY = player->getTransform()->getPosition().y + (player->getCollision()->getRectSize().l / 2);
            _entities.push_back(std::make_shared<Bullet>(false, Vector(10, 0), Vector(bulletPosX, bulletPosY)));
            player->popFirstInput();
        }
    }
}


void game_engine::SpawnSystem::checkEnnemyShoot(std::vector<std::shared_ptr<game_engine::IEntities>> newListEnnemy,
    std::vector<std::shared_ptr<game_engine::IEntities>> newListPlayer)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEnnemyIter;
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    game_engine::Enemy *ennemy;
    game_engine::Player *player;
    int bulletPosX = 0;
    int bulletPosY = 0;
    int vecBulletX = 0;
    int vecBulletY = 0;
    int playerSelected = 0;
    int i = 0;

    for (listEnnemyIter = newListEnnemy.begin(); listEnnemyIter != newListEnnemy.end(); listEnnemyIter++) {
        ennemy = static_cast<Enemy *>(listEnnemyIter->get());
        if (ennemy->getFirstEnum() == InputEnum::SHOOTINPUT) {
            bulletPosX = ennemy->getTransform()->getPosition().x;
            bulletPosY = ennemy->getTransform()->getPosition().y + (ennemy->getCollision()->getRectSize().l / 2);
            playerSelected = rand() % newListPlayer.size();
            for (listPlayerIter = newListPlayer.begin(); listPlayerIter != newListPlayer.end() && i != playerSelected; listPlayerIter++, i++);
            player = static_cast<Player *>(listPlayerIter->get());
            vecBulletX = player->getTransform()->getPosition().x - bulletPosX;
            vecBulletY = player->getTransform()->getPosition().y - bulletPosY;
            _entities.push_back(std::make_shared<Bullet>(false, Vector(vecBulletX, vecBulletY), Vector(bulletPosX, bulletPosY)));
            ennemy->popFirstInput();
        }
    }
}