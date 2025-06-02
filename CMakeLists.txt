cmake_minimum_required(VERSION 3.10)
project(HeroGame)

set(CMAKE_CXX_STANDARD 17)

# Kilde- og headerfiler
set(SOURCES
    main.cpp
    Hero.cpp
    Enemy.cpp
    Weapon.cpp
    Dungeon.cpp
    Database.cpp
)

set(HEADERS
    Hero.h
    Enemy.h
    Weapon.h
    Dungeon.h
    Database.h
)

# Find SQLite
find_package(SQLite3 REQUIRED)

# Byg eksekverbar
add_executable(hero_game ${SOURCES} ${HEADERS})

# Link SQLite
target_link_libraries(hero_game SQLite::SQLite3)

