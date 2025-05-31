#include "Dungeon.h"
#include "Database.h"
#include <iostream>

// Reuse global fightEnemy function declared in main.cpp
extern void fightEnemy(Hero& hero, Enemy enemy, bool resetHP);

Dungeon::Dungeon(std::string name, std::vector<Enemy> enemies)
    : name(name), enemies(enemies) {}

std::string Dungeon::getName() const {
    return name;
}

void Dungeon::enter(Hero& hero) {
    std::cout << "You enter the dungeon: " << name << "\n";

    for (Enemy& enemy : enemies) {
        fightEnemy(hero, enemy, false);  // Don't reset HP between fights
        if (hero.hp <= 0) {
            std::cout << "You were defeated in the dungeon!\n";
            return;
        }
    }

    std::cout << "You cleared the dungeon: " << name << "\n";
}

