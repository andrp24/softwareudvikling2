#include "Hero.h"
#include "Enemy.h"
#include "Database.h"
#include <iostream>
#include <vector>

Hero createNewHero() {
    std::string name;
    std::cout << "Enter your hero's name: ";
    std::getline(std::cin, name);
    Hero hero(name);
    Database::saveHero(hero);
    return hero;
}

Hero loadExistingHero() {
    std::cout << "Available heroes:\n";
    Database::listHeroes();
    std::string name;
    std::cout << "Enter name to load: ";
    std::getline(std::cin, name);
    return Database::loadHero(name);
}

std::vector<Enemy> createEnemyList() {
    return {
        Enemy("Weak Goblin", 4, 2, 200, 20),
        Enemy("Strong Goblin", 8, 4, 400, 50),
        Enemy("Stronger Goblin", 10, 6, 500, 70),
        Enemy("Mighty Goblin", 12, 8, 600, 100),
        Enemy("KingApe", 20, 10, 1000, 200)
    };
}

void fightEnemy(Hero& hero, Enemy enemy) {
    std::cout << "You are fighting: " << enemy.name << " with " << enemy.hp << " hp\n";
    while (hero.hp > 0 && enemy.hp > 0) {
        enemy.hp -= hero.strength;
        if (enemy.hp > 0) {
            hero.hp -= enemy.strength;
        }
    }

    if (hero.hp > 0) {
        std::cout << "You won!\n";
        hero.gainXP(enemy.xpReward);
        hero.gainGold(enemy.goldReward);
    } else {
        std::cout << "You were defeated!\n";
    }

    hero.restoreHP(); // Reset HP after battle
    Database::saveHero(hero);
}

int main() {
    Database::initDB();
    Hero hero("");

    std::cout << "(0) New Game  (1) Load Game: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // flush newline

    if (choice == 0) {
        hero = createNewHero();
    } else {
        hero = loadExistingHero();
    }

    std::vector<Enemy> enemies = createEnemyList();

    while (true) {
        std::cout << "\n";
        hero.display();
        std::cout << "Choose enemy to fight:\n";
        for (size_t i = 0; i < enemies.size(); ++i) {
            std::cout << i << ": " << enemies[i].name << "\n";
        }
        std::cout << "Your choice (or 9 to quit): ";
        int enemyIndex;
        std::cin >> enemyIndex;
        std::cin.ignore();

        if (enemyIndex == 9) break;
        if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
            fightEnemy(hero, enemies[enemyIndex]);
        }
    }

    return 0;
}
