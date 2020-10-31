cmake_minimum_required(VERSION 3.5)
project(r-type)

include(${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# ==== SERVER ====

set(SERVER_SRCS
    ./server/main.cpp
    ./server/game_engine/src/System.cpp
    ./server/game_engine/src/Entities/Bullet.cpp
    ./server/game_engine/src/Entities/DestroyableTile.cpp
    ./server/game_engine/src/Entities/Enemy.cpp
    ./server/game_engine/src/Entities/Environment.cpp
    ./server/game_engine/src/Entities/Player.cpp
    ./server/game_engine/src/Entities/PowerUp.cpp
    ./server/game_engine/src/Entities/StageObstacle.cpp
)

add_executable(r-type_server ${SERVER_SRCS})

target_link_libraries(r-type_server CONAN_PKG::boost)
target_include_directories(r-type_server PUBLIC 
    ./server/game_engine/include
    ./server/game_engine/include/Entities
    ./server/game_engine/include/Components
)

# ==== CLIENT ====

set(CLIENT_SRCS
    ./client/src/main.cpp
    ./client/src/Client.cpp
    ./client/src/ErrorHandler.cpp
    ./client/src/WindowHandler.cpp
    ./client/src/Entities/Monster.cpp
    ./client/src/Entities/Player.cpp
    ./client/src/Entities/SMonster.cpp
    ./client/src/SFML/BackgroundSFML.cpp
    ./client/src/SFML/ImageSFML.cpp
    ./client/src/SFML/TextSFML.cpp
    ./client/src/Virtual/VEntitie.cpp
    ./client/src/Virtual/VMonster.cpp
)

add_executable(r-type_server ${SERVER_SRCS})

target_link_libraries(r-type_server CONAN_PKG::boost)
target_include_directories(r-type_server PUBLIC
    ./client/include
    ./client/Class/Entities/
    ./client/Class/
    ./client/Class/SFML/
    ./client/Class/Virtual/
)
