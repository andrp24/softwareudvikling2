#ifndef HERO_H
#define HERO_H

#include <string>
#include <map>
#include "Weapon.h"

class Hero {
public:
    std::string name;
    int hp;
    int maxHp;
    int level;
    int xp;
    int gold;
    int strength;
    int totalKills;
    int weaponKills;
    Weapon* weapon;
    std::map<std::string, int> weaponKillHistory; // våben-historik

    Hero(std::string name);

    void gainXP(int amount);
    void gainGold(int amount);
    void levelUp();
    void equipWeapon(Weapon* newWeapon);
    int attack() const;
};

#endif
