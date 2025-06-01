#include "Dungeon.h"
#include "Database.h"
#include "Weapon.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

extern void fightEnemy(Hero& hero, Enemy enemy, bool resetHP);

Dungeon::Dungeon(std::string name, std::vector<Enemy> enemies, int bonusGold)
    : name(name), enemies(enemies), bonusGold(bonusGold) {}

std::string Dungeon::getName() const {
    return name;
}

void Dungeon::enter(Hero& hero) {
    std::cout << "You enter the dungeon: " << name << "\n";
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    double levelScale = 1.0 + (hero.level * 0.10); // 10% per level
    struct Modifier {
        std::string prefix;
        double multiplier;
    };

    std::vector<Modifier> modifiers = {
        {"Weak", 0.8},
        {"", 1.0},
        {"Strong", 1.2},
        {"Mighty", 1.4},
        {"Elite", 1.6},
        {"Legendary", 1.8}
    };

    auto randomize = [](int base) {
        double variation = ((std::rand() % 21) - 10) / 100.0;
        return std::round(base * (1.0 + variation));
    };

    for (Enemy enemy : enemies) {
        Modifier mod;
        int roll = std::rand() % 100;
        if (roll < 70) {
            mod = modifiers[std::rand() % modifiers.size()];
        } else {
            mod = {"", 1.0};
        }

        double totalScale = levelScale * mod.multiplier;
        std::string modifiedName = mod.prefix.empty() ? enemy.name : mod.prefix + " " + enemy.name;
        enemy.hp = randomize(std::round(enemy.hp * totalScale));
        enemy.strength = randomize(std::round(enemy.strength * totalScale));
        enemy.xpReward = randomize(std::round(enemy.xpReward * totalScale));
        enemy.goldReward = std::round(enemy.goldReward * totalScale);

        std::cout << "Fighting: " << modifiedName
                  << " (HP: " << enemy.hp
                  << ", STR: " << enemy.strength
                  << ", XP: " << enemy.xpReward
                  << ", Gold: " << enemy.goldReward << ")\n";

        fightEnemy(hero, enemy, false);
        if (hero.hp <= 0) {
            std::cout << "You were defeated in the dungeon!\n";
            return;
        }

        hero.totalKills++;
        if (hero.weapon && !hero.weapon->isBroken()) {
            hero.weaponKills++;
        }
    }

    std::cout << "You cleared the dungeon: " << name << "!\n";
    std::cout << "You earn a bonus of " << bonusGold << " gold for clearing it!\n";
    hero.gainGold(bonusGold);

    
    
    std::vector<Weapon> dungeonRewards = {
       Weapon("Sword", 3, 1.0, 10),
       Weapon("Axe", 5, 1.2, 15),
       Weapon("Blade", 8, 1.4, 20),
       Weapon("Mace", 12, 1.6, 25),
       Weapon("???", 30, 3.0, 100)
    };

    Weapon droppedWeapon = dungeonRewards[std::rand() % dungeonRewards.size()];

    std::cout << "You found a weapon: " << droppedWeapon.getName()
              << " (DMG: " << droppedWeapon.getBaseDamage()
              << ", STRx" << droppedWeapon.getStrengthModifier()
              << ", Durability: " << droppedWeapon.getDurability() << ")!\n";

    if (hero.weapon != nullptr) {
        std::cout << "\nYour current weapon: " << hero.weapon->getName()
                  << " (DMG: " << hero.weapon->getBaseDamage()
                  << ", STRx" << hero.weapon->getStrengthModifier()
                  << ", Durability: " << hero.weapon->getDurability() << ")\n";
        std::cout << "Do you want to replace your current weapon with the new one? (y/n): ";
        char decision;
        std::cin >> decision;

        if (decision == 'y' || decision == 'Y') {
            hero.equipWeapon(new Weapon(droppedWeapon));
            std::cout << "You equipped the new weapon!\n";
        } else {
            std::cout << "You chose to keep your current weapon. The dungeon weapon is lost.\n";
        }
    } else {
        hero.equipWeapon(new Weapon(droppedWeapon));
        std::cout << "You had no weapon, so you automatically equipped the new one.\n";
    }
}
