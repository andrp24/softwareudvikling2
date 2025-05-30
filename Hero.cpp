#include "Hero.h"
#include "Enemy.h"
#include <iostream>
#include <sstream>

Hero::Hero(const std::string& name)
    : name(name), xp(0), level(1), hp(10), damage(2) {}

Hero::Hero(const std::string& name, int level, int hp, int xp, int damage)
    : name(name), level(level), hp(hp), xp(xp), damage(damage) {}

void Hero::gainXP(int xpGained) {
    if (xpGained > 0) xp += xpGained;
    else hp += xpGained;
    if (xp >= level * 1000) levelUp();
}

void Hero::attack(Enemy& enemy) {
    enemy.takeDamage(damage);
    if (!enemy.isAlive()) gainXP(enemy.getXP());
}

void Hero::levelUp() {
    xp = 0;
    level++;
    hp += 2;
    damage++;
    std::cout << name << " leveled up to level " << level << "!\n";
}

void Hero::printStatus() const {
    std::cout << name << " (Level: " << level << ", HP: " << hp << ", XP: " << xp << ")\n";
}

const std::string& Hero::getName() const { return name; }
int Hero::getHP() const { return hp; }
int Hero::getLevel() const { return level; }
int Hero::getXP() const { return xp; }
int Hero::getDamage() const { return damage; }
bool Hero::isAlive() const { return hp > 0; }

std::string Hero::serialize() const {
    std::ostringstream oss;
    oss << name << "," << level << "," << hp << "," << xp << "," << damage;
    return oss.str();
}

Hero Hero::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string name;
    int level, hp, xp, damage;
    std::getline(iss, name, ',');
    iss >> level; iss.ignore();
    iss >> hp; iss.ignore();
    iss >> xp; iss.ignore();
    iss >> damage;
    return Hero(name, level, hp, xp, damage);
}
