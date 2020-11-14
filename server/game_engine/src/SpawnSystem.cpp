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
    blockSpawnChrono = std::chrono::high_resolution_clock::now();
    enemySpawnChrono = std::chrono::high_resolution_clock::now();
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
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    int enemyChancetoSpawn;

    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - enemySpawnChrono).count() >= 2500) {
        //std::cout << "spawn enemy" << std::endl;
        enemySpawnChrono = std::chrono::high_resolution_clock::now();
        for (int nb = rand() % 3; nb >= 0; nb--) {
            int x = rand() % _enemyLoader.size();
            _entities->push_back(_enemyLoader[x].getInstance("entryPoint", Vector(1920, (rand() % 780) + 50), getAndIncID()));
        }
        setEnnemyRender();
    }
}

void game_engine::SpawnSystem::setEnnemyRender()
{
    std::vector<std::shared_ptr<AComponents>> entitiesComponents;
    std::vector<std::shared_ptr<AComponents>>::iterator componentListIter;
    Render *entitieRenderComponent;
    Health *entitieHealthComponent;

    entitiesComponents = (*_entities)[_entities->size() - 1].get()->getComponentList();
    for (componentListIter = entitiesComponents.begin(); componentListIter != entitiesComponents.end(); ++componentListIter) {
        if (componentListIter->get()->getType() == ComponentType::RENDER)
            entitieRenderComponent = static_cast<Render *>(componentListIter->get());
        if (componentListIter->get()->getType() == ComponentType::HEALTH)
            entitieHealthComponent = static_cast<Health *>(componentListIter->get());
    }
    if ((*_entities)[_entities->size() - 1].get()->getEntitiesID() == EntitiesType::ENEMYALIEN)
        entitieRenderComponent->setRect(game_engine::Rectangle(0, 67, 33, 36));
    if ((*_entities)[_entities->size() - 1].get()->getEntitiesID() == EntitiesType::ENEMYBATTLESHIP)
        entitieRenderComponent->setRect(game_engine::Rectangle(0, 0, 65, 50));
    if ((*_entities)[_entities->size() - 1].get()->getEntitiesID() == EntitiesType::ENEMYTROOPER)
        entitieRenderComponent->setRect(game_engine::Rectangle(18, 68, 33, 30));
    entitieHealthComponent->setIsDamageable(true);
    entitieHealthComponent->setHealthPoint(1);
}

int game_engine::SpawnSystem::newPlayer(boost::asio::ip::udp::endpoint &endpoint)
{
    std::shared_ptr<std::vector<std::shared_ptr<game_engine::IEntities>>> newListPlayer = std::make_shared<std::vector<std::shared_ptr<IEntities>>>();
    std::shared_ptr<Player> newPlayer;

    newListPlayer = EntitiesParser::getEntities(std::vector<game_engine::EntitiesType>{game_engine::EntitiesType::PLAYER}, _entities);
    if (newListPlayer->size() == 0)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Blue, getAndIncID(), endpoint);
    if (newListPlayer->size() == 1)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Red, getAndIncID(), endpoint);
    if (newListPlayer->size() == 2)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Yellow, getAndIncID(), endpoint);
    if (newListPlayer->size() == 3)
        newPlayer = std::make_shared<Player>(Vector(50, 500), PlayerColor::Green, getAndIncID(), endpoint);
    _entities->push_back(newPlayer);
    return (getID());
}

void game_engine::SpawnSystem::spawnObstacle()
{
    int obstacleChancetoSpawn;
    int nbObstacletoSpawn;
    int upOrDownSpawn;

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - blockSpawnChrono).count() >= 200) {
        //std::cout << "spawn block" << std::endl;
        blockSpawnChrono = std::chrono::high_resolution_clock::now();

        _entities->push_back(std::make_shared<StageObstacle>(Vector(1920, 0), getAndIncID()));
        _entities->push_back(std::make_shared<StageObstacle>(Vector(1920, 960), getAndIncID()));
        addObstacle();
    }
}

void game_engine::SpawnSystem::addObstacle()
{
    int obstacleChancetoSpawn;
    int nbObstacletoSpawn;
    int upStart = 60;
    int downStart = 960;
    int stageObstacleOrNot;

    obstacleChancetoSpawn = rand() % 6;
    if (obstacleChancetoSpawn == 1) {
        nbObstacletoSpawn = rand() % 4 + 1;
        for (upStart = 60; upStart <= nbObstacletoSpawn * 60; upStart += 60) {
            stageObstacleOrNot = rand() % 2;
            if (stageObstacleOrNot == 0)
                _entities->push_back(std::make_shared<StageObstacle>(Vector(1920, ((upStart + rand()) % 16) * 60), getAndIncID()));
            else
                _entities->push_back(std::make_shared<DestroyableTile>(Vector(1920, ((upStart + rand()) % 16) * 60), getAndIncID()));
        }
    }
}

void game_engine::SpawnSystem::checkEntitieShoot()
{
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
            _entities->push_back(std::make_shared<Bullet>(false, Vector(30, 0), Vector(bulletPosX, bulletPosY), getAndIncID()));
            player->popFirstInput();
        }
    }
}

void game_engine::SpawnSystem::checkEnnemyShoot(std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListEnnemy,
    std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListPlayer)
{
    std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listEnnemyIter;
    //std::vector<std::shared_ptr<game_engine::IEntities>>::iterator listPlayerIter;
    game_engine::Enemy *ennemy;
    //game_engine::Player *player;
    int bulletPosX = 0;
    int bulletPosY = 0;
    int vecBulletX = 0;
    int vecBulletY = 0;
    //int playerSelected = 0;
    int i = 0;

    for (listEnnemyIter = newListEnnemy->begin(); listEnnemyIter != newListEnnemy->end(); listEnnemyIter++) {
        ennemy = static_cast<Enemy *>(listEnnemyIter->get());
        if (ennemy->getFirstEnum() == InputEnum::SHOOTINPUT) {
            bulletPosX = ennemy->getTransform()->getPosition().x;
            bulletPosY = ennemy->getTransform()->getPosition().y + (ennemy->getCollision()->getRectSize().l / 2);
            //playerSelected = rand() % newListPlayer->size();
            //for (listPlayerIter = newListPlayer->begin(); listPlayerIter != newListPlayer->end() && i != playerSelected; listPlayerIter++, i++);
            //player = static_cast<Player *>(listPlayerIter->get());
            vecBulletX = -10;
            vecBulletY = 0;
            _entities->push_back(std::make_shared<Bullet>(true, Vector(vecBulletX, vecBulletY), Vector(bulletPosX, bulletPosY), getAndIncID()));
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