#include "Hero.h"
#include <iostream>
#include <cmath>

Hero::Hero(std::string name)
    : name(name), hp(10), maxHp(10), level(1), xp(0), gold(0), strength(2),
      totalKills(0), weaponKills(0), weapon(nullptr) {}

void Hero::gainXP(int amount) {
    xp += amount;
    std::cout << "You gain " << amount << " XP!\n";

    while (xp >= level * 1000) {
        xp -= level * 1000;
        levelUp();
    }
}

void Hero::gainGold(int amount) {
    gold += amount;
    std::cout << "You gain " << amount << " gold!\n";
}

void Hero::levelUp() {
    level++;
    std::cout << "You leveled up! Now level " << level << "!\n";

    std::cout << "Choose stat to increase:\n";
    std::cout << "1. +2 Strength\n";
    std::cout << "2. +25 Max HP\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        strength += 2;
    } else {
        maxHp += 25;
    }

    hp = maxHp;
    std::cout << "HP fully restored!\n";
}

void Hero::equipWeapon(Weapon* newWeapon) {
    weapon = newWeapon;
    std::cout << "Equipped weapon: " << weapon->getName() << "\n";
}

int Hero::attack() const {
    if (weapon && !weapon->isBroken()) {
        return weapon->getBaseDamage() + static_cast<int>(strength * weapon->getStrengthModifier());
    } else {
        return strength;
    }
}
