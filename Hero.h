#ifndef HERO_H
#define HERO_H

#include <string>

class Hero {
public:
    Hero(const std::string& name);
    Hero(const std::string& name, int level, int hp, int xp, int damage);
    void gainXP(int xp);
    void attack(class Enemy& enemy);
    void printStatus() const;

    const std::string& getName() const;
    int getHP() const;
    int getLevel() const;
    int getXP() const;
    int getDamage() const;
    bool isAlive() const;

    std::string serialize() const;
    static Hero deserialize(const std::string& data);

private:
    std::string name;
    int xp;
    int level;
    int hp;
    int damage;

    void levelUp();
};

#endif
