#include "Dungeon.h"
#include "Database.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Reuse global fightEnemy function declared in main.cpp
extern void fightEnemy(Hero& hero, Enemy enemy, bool resetHP);

Dungeon::Dungeon(std::string name, std::vector<Enemy> enemies, int bonusGold)
    : name(name), enemies(enemies), bonusGold(bonusGold) {}

std::string Dungeon::getName() const {
    return name;
}

void Dungeon::enter(Hero& hero) {
    std::cout << "You enter the dungeon: " << name << "\n";

    std::srand(static_cast<unsigned>(std::time(nullptr))); // Init random generator
    double scale = 1.0 + (hero.level * 0.10); // 10% per level

    auto randomize = [](int base) {
        double variation = ((std::rand() % 21) - 10) / 100.0; // -10% til +10%
        return std::round(base * (1.0 + variation));
    };

    for (Enemy enemy : enemies) {
        // Skalér + randomiser stats
        enemy.hp = randomize(std::round(enemy.hp * scale));
        enemy.strength = randomize(std::round(enemy.strength * scale));
        enemy.xpReward = randomize(std::round(enemy.xpReward * scale));
        enemy.goldReward = std::round(enemy.goldReward * scale);

        std::cout << "Fighting: " << enemy.name
                  << " (HP: " << enemy.hp
                  << ", STR: " << enemy.strength
                  << ", XP: " << enemy.xpReward
                  << ", Gold: " << enemy.goldReward << ")\n";

        fightEnemy(hero, enemy, false);

        if (hero.hp <= 0) {
            std::cout << "You were defeated in the dungeon!\n";
            return;
        }
    }

    std::cout << "You cleared the dungeon: " << name << "!\n";
    std::cout << "You earn a bonus of " << bonusGold << " gold for clearing it!\n";
    hero.gainGold(bonusGold);
}
