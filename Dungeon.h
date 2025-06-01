#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include "Enemy.h"
#include "Hero.h"

class Dungeon {
public:
    Dungeon(std::string name, std::vector<Enemy> enemies, int bonusGold);
    void enter(Hero& hero);
    std::string getName() const;

private:
    std::string name;
    std::vector<Enemy> enemies;
    int bonusGold;
};

#endif
