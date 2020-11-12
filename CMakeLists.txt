cmake_minimum_required(VERSION 3.5)
project(r-type)

SET(CMAKE_CXX_FLAGS "-ldl")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# ==== SERVER ====

set(SERVER_SRCS
    ./server/main.cpp
    ./server/game_engine/src/GameLoop.cpp
    ./server/game_engine/src/Exception.cpp
    ./server/game_engine/src/System.cpp
    ./server/game_engine/src/Exception.cpp
    ./server/game_engine/src/MoveSystem.cpp
    ./server/game_engine/src/DeathSystem.cpp
    ./server/game_engine/src/SpawnSystem.cpp
    ./server/game_engine/src/DamageSystem.cpp
    ./server/game_engine/src/CollisionSystem.cpp
    ./server/game_engine/src/Entities/Bullet.cpp
    ./server/game_engine/src/Entities/DestroyableTile.cpp
    ./server/game_engine/src/Entities/Player.cpp
    ./server/game_engine/src/Entities/PowerUp.cpp
    ./server/game_engine/src/Entities/StageObstacle.cpp
    ./server/src/NetUDPServer.cpp
    ./server/src/NetTCPServer.cpp
    ./server/src/NetTCPRoom.cpp
    ./server/src/NetTCPServerClient.cpp
)

add_executable(r-type_server ${SERVER_SRCS})

target_link_libraries(r-type_server CONAN_PKG::boost)
target_include_directories(r-type_server PUBLIC
    ${CONAN_INCLUDE_DIRS_BOOST}
    ./server/game_engine/include
    ./server/game_engine/include/Entities
    ./server/game_engine/include/Components
    ./server/include/
)

# ==== CLIENT ====

set(CLIENT_SRCS
    ./client/main.cpp
    ./client/src/Env/ErrorHandler.cpp
    ./client/src/Env/Exception.cpp
    ./client/src/Entities/Entities.cpp
    ./client/src/Entities/Player.cpp
    ./client/src/Game/Animation.cpp
    ./client/src/Game/Client.cpp
    ./client/src/Game/MusicSystem.cpp
    ./client/src/Game/WindowHandler.cpp
    ./client/src/SFML/BackgroundSFML.cpp
    ./client/src/SFML/ImageSFML.cpp
    ./client/src/SFML/MusicSFML.cpp
    ./client/src/SFML/TextSFML.cpp
    ./client/src/SFML/Button.cpp
    ./client/src/Menu/Main.cpp
    ./client/src/Menu/Room.cpp
    ./client/src/Network/NetUDPClient.cpp
    ./client/src/Network/NetTCPClient.cpp
)

add_executable(r-type_client ${CLIENT_SRCS})

target_link_libraries(r-type_client CONAN_PKG::boost CONAN_PKG::sfml)
target_include_directories(r-type_client PUBLIC
    ${CONAN_INCLUDE_DIRS_BOOST}
    ${CONAN_INCLUDE_DIRS_SFML}
    ./client/include
    ./client/Class/
    ./client/Class/Entities/
    ./client/Class/Env/
    ./client/Class/Game/
    ./client/Class/Menu/
    ./client/Class/SFML/
)
