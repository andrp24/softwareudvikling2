#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    std::string name;
    int hp;
    int strength;
    int xpReward;
    int goldReward;

    Enemy(std::string n, int h, int s, int xp, int gold);
};

#endif
