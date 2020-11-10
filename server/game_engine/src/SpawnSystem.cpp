/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SpawnSystem
*/

#include "SpawnSystem.hpp"

game_engine::SpawnSystem::SpawnSystem()
{
    DIR *pDIR;
    std::string file;
    struct dirent *entry;
    DDloader<game_engine::Enemy> libLoader;
    std::vector<std::string> enemyLib;

    pDIR = opendir("./lib");
    if (pDIR == nullptr)
        throw (Exception("Can't find ennemy directory"));
    while (entry = readdir(pDIR)) {
        file.assign(entry->d_name);
        if (file.find(".so") != std::string::npos) {
            file.insert(0, "./lib/");
            enemyLib.push_back(file);
        }
    }
    closedir(pDIR);

    if (enemyLib.size() == 0)
        throw (Exception("No library found in ennemy directory"));
    for (int i = 0; i < 3; i++) {
        if (libLoader.loadLibrary(enemyLib[i].c_str()) == 84)
            throw (Exception("can't load"));
        _enemyLoader.push_back(libLoader);
    }
}

game_engine::SpawnSystem::SpawnSystem(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> entities): _entities(entities)
{
    DIR *pDIR;
    std::string file;
    struct dirent *entry;
    DDloader<game_engine::Enemy> libLoader;
    std::vector<std::string> enemyLib;

    pDIR = opendir("./lib");
    if (pDIR == nullptr)
        throw (Exception("Can't find ennemy directory"));
    while (entry = readdir(pDIR)) {
        file.assign(entry->d_name);
        if (file.find(".so") != std::string::npos) {
            file.insert(0, "./lib/");
            enemyLib.push_back(file);
        }
    }
    closedir(pDIR);

    if (enemyLib.size() == 0)
        throw (Exception("No library found in ennemy directory"));
    for (int i = 0; i < 3; i++) {
        if (libLoader.loadLibrary(enemyLib[i].c_str()) == 84)
            throw (Exception("can't load"));
        _enemyLoader.push_back(libLoader);
    }
    blockSpawnClock = std::clock();
    blockSpawnClock = 0.5;
    enemySpawnClock = std::clock();
    enemySpawnClock = 2;
    id = 1;
}

game_engine::SpawnSystem::~SpawnSystem()
{
    int size = _enemyLoader.size();

    for (int i = 0; i < size; i++)
        _enemyLoader[i].closeLibrary();
}

game_engine::SpawnSystem &game_engine::SpawnSystem::operator=(const game_engine::SpawnSystem &spawnSystem)
{
    _entities = spawnSystem._entities;
    return (*this);
}


void game_engine::SpawnSystem::spawnSystem()
{
    spawnEnemy();
    spawnObstacle();
    checkEntitieShoot();
}

void game_engine::SpawnSystem::spawnEnemy()
{
    double timePassed = std::clock() - enemySpawnClock;
    int enemyChancetoSpawn;

    if (timePassed > enemySpawnTime) {
        enemySpawnClock = std::clock();
        enemySpawnClock = 2;
        int x = rand() % _enemyLoader.size();
        _entities->push_back(_enemyLoader[x].getInstance("entryPoint", Vector(1920, (rand() % 990) + 50), getAndIncID()));
    }
}

int game_engine::SpawnSystem::newPlayer()
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> newListPlayer = std::make_shared<std::vector<std::shared_ptr<IEntities>>>();
    std::shared_ptr<Player> newPlayer;

    newListPlayer = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    if (newListPlayer->size() == 0)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Yellow, getAndIncID());
    if (newListPlayer->size() == 1)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Blue, getAndIncID());
    if (newListPlayer->size() == 2)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Red, getAndIncID());
    if (newListPlayer->size() == 3)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Green, getAndIncID());
    _entities->push_back(newPlayer);
    return (getID());
}

void game_engine::SpawnSystem::spawnObstacle()
{
    double timePassed = std::clock() - blockSpawnClock;
    int obstacleChancetoSpawn;
    int nbObstacletoSpawn;
    int upOrDownSpawn;

    if (timePassed > blockSpawnTime) {
        blockSpawnClock = std::clock();
        blockSpawnClock = 0.5;
        _entities->push_back(std::make_shared<StageObstacle>(Vector(0, 1920), getAndIncID()));
        _entities->push_back(std::make_shared<StageObstacle>(Vector(1030, 1920), getAndIncID()));
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
                    _entities->push_back(std::make_shared<StageObstacle>(Vector(upStart, 1920), getAndIncID()));
                else
                    _entities->push_back(std::make_shared<DestroyableTile>(Vector(upStart, 1920), getAndIncID()));
            }
        }
        else {
            for (downStart = 1040; downStart <= 1040 - 50 * nbObstacletoSpawn; downStart-=50) {
                stageObstacleOrNot = rand() % 2;
                if (stageObstacleOrNot == 0)
                    _entities->push_back(std::make_shared<StageObstacle>(Vector(downStart, 1920), getAndIncID()));
                else
                    _entities->push_back(std::make_shared<DestroyableTile>(Vector(downStart, 1920), getAndIncID()));
            }
        }
    }
}

void game_engine::SpawnSystem::checkEntitieShoot()
{
    //EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities, newListPlayer);
    //EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMY}, _entities, newListEnnemy);
    checkPlayerShoot(EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities));
    checkEnnemyShoot(EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::ENEMYALIEN,
        game_engine::EntitiesType::ENEMYBATTLESHIP, game_engine::EntitiesType::ENEMYTROOPER}, _entities),
        EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities));
}

void game_engine::SpawnSystem::checkPlayerShoot(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListPlayer)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    game_engine::Player *player;
    int bulletPosX = 0;
    int bulletPosY = 0;

    for (listPlayerIter = newListPlayer->begin(); listPlayerIter != newListPlayer->end(); listPlayerIter++) {
        player = static_cast<Player *>(listPlayerIter->get());
        if (player->getFirstEnum() == InputEnum::SHOOTINPUT) {
            bulletPosX = player->getTransform()->getPosition().x + player->getCollision()->getRectSize().L;
            bulletPosY = player->getTransform()->getPosition().y + (player->getCollision()->getRectSize().l / 2);
            _entities->push_back(std::make_shared<Bullet>(false, Vector(10, 0), Vector(bulletPosX, bulletPosY), getAndIncID()));
            player->popFirstInput();
        }
    }
}


void game_engine::SpawnSystem::checkEnnemyShoot(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListEnnemy,
    std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListPlayer)
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

    for (listEnnemyIter = newListEnnemy->begin(); listEnnemyIter != newListEnnemy->end(); listEnnemyIter++) {
        ennemy = static_cast<Enemy *>(listEnnemyIter->get());
        if (ennemy->getFirstEnum() == InputEnum::SHOOTINPUT) {
            bulletPosX = ennemy->getTransform()->getPosition().x;
            bulletPosY = ennemy->getTransform()->getPosition().y + (ennemy->getCollision()->getRectSize().l / 2);
            playerSelected = rand() % newListPlayer->size();
            for (listPlayerIter = newListPlayer->begin(); listPlayerIter != newListPlayer->end() && i != playerSelected; listPlayerIter++, i++);
            player = static_cast<Player *>(listPlayerIter->get());
            vecBulletX = player->getTransform()->getPosition().x - bulletPosX;
            vecBulletY = player->getTransform()->getPosition().y - bulletPosY;
            _entities->push_back(std::make_shared<Bullet>(false, Vector(vecBulletX, vecBulletY), Vector(bulletPosX, bulletPosY), getAndIncID()));
            ennemy->popFirstInput();
        }
    }
}

int game_engine::SpawnSystem::getAndIncID()
{
    int temp = id;

    id++;
    return (temp);
}

int game_engine::SpawnSystem::getID() const
{
    return (id);
}
void game_engine::SpawnSystem::incID()
{
    id++;
}