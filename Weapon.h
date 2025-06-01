#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
public:
    Weapon(std::string name, int baseDamage, double strengthModifier, int durability);

    int getBaseDamage() const;
    double getStrengthModifier() const;
    int getDurability() const;
    std::string getName() const;

    int use(int heroStrength); // returns damage, reduces durability
    bool isBroken() const;

private:
    std::string name;
    int baseDamage;
    double strengthModifier;
    int durability;
};

#endif

