#include "Weapon.h"
#include <iostream>

Weapon::Weapon(std::string name, int baseDamage, double strengthModifier, int durability)
    : name(name), baseDamage(baseDamage), strengthModifier(strengthModifier), durability(durability) {}

int Weapon::getBaseDamage() const {
    return baseDamage;
}

double Weapon::getStrengthModifier() const {
    return strengthModifier;
}

int Weapon::getDurability() const {
    return durability;
}

std::string Weapon::getName() const {
    return name;
}

int Weapon::use(int heroStrength) {
    if (durability <= 0) {
        std::cout << "Weapon " << name << " is broken and can't be used!\n";
        return 0;
    }

    durability--;
    return static_cast<int>(baseDamage + (heroStrength * strengthModifier));
}

bool Weapon::isBroken() const {
    return durability <= 0;
}

