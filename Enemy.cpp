#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& name, int hp, int damage, int xp)
    : name(name), hp(hp), damage(damage), xp(xp) {}

const std::string& Enemy::getName() const { return name; }
int Enemy::getHP() const { return hp; }
int Enemy::getDamage() const { return damage; }
int Enemy::getXP() const { return xp; }
bool Enemy::isAlive() const { return hp > 0; }

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

void Enemy::printStatus() const {
    std::cout << name << " (HP: " << hp << ", Damage: " << damage << ", XP: " << xp << ")\n";
}

