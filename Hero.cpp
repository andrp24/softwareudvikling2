#include "Hero.h"
#include <iostream>
#include <fstream>

Hero::Hero() : name("Unnamed"), xp(0), level(1), hitpoints(100), strength(10) {}

Hero::Hero(std::string name, int level, int hitpoints, int strength)
    : name(name), xp(0), level(level), hitpoints(hitpoints), strength(strength) {}

void Hero::saveHero() const {
    std::ofstream file(name + ".txt");
    if (file.is_open()) {
        file << name << "\n" << xp << "\n" << level << "\n" << hitpoints << "\n" << strength;
        file.close();
    }
}

bool Hero::loadHero(const std::string &heroName) {
    std::ifstream file(heroName + ".txt");
    if (!file.is_open()) {
        return false;
    }

    file >> name >> xp >> level >> hitpoints >> strength;
    file.close();
    return true;
}

void Hero::displayStats() const {
    std::cout << "Name: " << name << "\nLevel: " << level << "\nXP: " << xp
              << "\nHitpoints: " << hitpoints << "\nStrength: " << strength << "\n";
}

