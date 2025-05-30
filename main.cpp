#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Hero.h"
#include "Enemy.h"

void printEnemies(const std::vector<Enemy>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << i + 1 << ". ";
        enemies[i].printStatus();
    }
}

void saveHero(const Hero& hero) {
    std::ofstream file("heroes.txt", std::ios::app);
    file << hero.serialize() << "\n";
}

Hero loadHero() {
    std::ifstream file("heroes.txt");
    std::vector<std::string> heroes;
    std::string line;
    int index = 1;
    while (std::getline(file, line)) {
        std::cout << index++ << ": " << line << "\n";
        heroes.push_back(line);
    }
    std::cout << "Choose hero to load: ";
    int choice;
    std::cin >> choice;
    return Hero::deserialize(heroes[choice - 1]);
}

int main() {
    Hero hero("Default");
    bool running = true;

    while (running) {
        std::cout << "\n1. Create new hero\n2. Load hero\n3. Exit\nChoice: ";
        int menuChoice;
        std::cin >> menuChoice;
        if (menuChoice == 1) {
            std::string name;
            std::cout << "Enter hero name: ";
            std::cin >> name;
            hero = Hero(name);
            saveHero(hero);
        } else if (menuChoice == 2) {
            hero = loadHero();
        } else {
            return 0;
        }

        std::vector<Enemy> enemies = {
            {"Hest", 4, 1, 100},
            {"Weak Goblin", 4, 2, 200},
            {"Strong Goblin", 8, 4, 300},
            {"Stronger Goblin", 10, 8, 500},
            {"Den stærkeste Goblin", 15, 5, 800},
            {"Abe Kongen", 30, 5, 1000},
            {"Enhjørning", 5, 8, 1500}
        };

        while (hero.isAlive()) {
            std::cout << "\nHero status: ";
            hero.printStatus();

            std::cout << "\nEnemies:\n";
            printEnemies(enemies);

            std::cout << "Choose enemy to fight (0 to save and exit): ";
            int choice;
            std::cin >> choice;

            if (choice == 0) {
                saveHero(hero);
                break;
            }
            if (choice < 1 || choice > enemies.size()) continue;

            Enemy& enemy = enemies[choice - 1];
            while (enemy.isAlive() && hero.isAlive()) {
                hero.attack(enemy);
                if (enemy.isAlive()) {
                    std::cout << enemy.getName() << " attacks back!\n";
                    hero.gainXP(-enemy.getDamage());
                }
            }
        }
    }

    std::cout << "Game Over.\n";
    return 0;
}
