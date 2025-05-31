#ifndef HERO_H
#define HERO_H

#include <string>

class Hero {
public:
    std::string name;
    int hp;
    int maxHp;
    int level;
    int xp;
    int gold;
    int strength;

    Hero(std::string name, int hp = 10, int level = 1, int xp = 0, int gold = 0, int strength = 2);
    void gainXP(int amount);
    void gainGold(int amount);
    void levelUp();
    void restoreHP();
    void display();
};

#endif
