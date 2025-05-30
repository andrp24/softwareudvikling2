#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(const std::string& name, int hp, int damage, int xp);

    const std::string& getName() const;
    int getHP() const;
    int getDamage() const;
    int getXP() const;
    bool isAlive() const;

    void takeDamage(int dmg);
    void printStatus() const;

private:
    std::string name;
    int hp;
    int damage;
    int xp;
};

#endif
