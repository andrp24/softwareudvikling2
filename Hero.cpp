#include "Hero.h"
#include <iostream>

Hero::Hero(std::string n, int h, int l, int x, int g, int str)
    : name(n), hp(h), maxHp(h), level(l), xp(x), gold(g), strength(str) {}

void Hero::gainXP(int amount) {
    xp += amount;
    levelUp();
}

void Hero::gainGold(int amount) {
    gold += amount;
}

void Hero::levelUp() {
    while (xp >= level * 1000) {
        xp -= level * 1000;
        level++;
        std::cout << " Level up! You reached level " << level << "!\n";
        std::cout << "Choose your upgrade:\n(1) +5 HP\n(2) +2 Strength\n> ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            maxHp += 5;
            std::cout << "Your max HP increased to " << maxHp << "!\n";
        } else {
            strength += 2;
            std::cout << "Your strength increased to " << strength << "!\n";
        }
        hp = maxHp;
    }
}

void Hero::restoreHP() {
    hp = maxHp;
}

void Hero::display() {
    std::cout << name << " - HP: " << hp << "/" << maxHp << ", Level: " << level
              << ", XP: " << xp << ", Gold: " << gold << ", Strength: " << strength << "\n";
}
