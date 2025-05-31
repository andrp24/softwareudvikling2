#ifndef DUNGEON_H
#define DUNGEON_H

#include "Hero.h"
#include "Enemy.h"
#include <vector>
#include <string>

class Dungeon {
public:
    Dungeon(std::string name, std::vector<Enemy> enemies);

    void enter(Hero& hero);
    std::string getName() const;

private:
    std::string name;
    std::vector<Enemy> enemies;
};

#endif

