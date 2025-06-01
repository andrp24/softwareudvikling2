#include <iostream>
#include <vector>
#include <map>
#include "Hero.h"
#include "Enemy.h"
#include "Database.h"
#include "Dungeon.h"
#include "Weapon.h"

void fightEnemy(Hero& hero, Enemy enemy, bool resetHP) {
    if (resetHP) {
        hero.hp = hero.maxHp;
    }

    std::cout << "A wild " << enemy.name << " appears!\n";

    while (hero.hp > 0 && enemy.hp > 0) {
        int damage = hero.attack();
        enemy.hp -= damage;
        std::cout << "You hit " << enemy.name << " for " << damage << " damage. "
                  << "Enemy HP: " << std::max(0, enemy.hp) << "\n";

        if (enemy.hp <= 0) {
            std::cout << enemy.name << " defeated!\n";
            hero.gainXP(enemy.xpReward);
            hero.gainGold(enemy.goldReward);
            hero.totalKills++;
            if (hero.weapon && !hero.weapon->isBroken()) {
                hero.weaponKills++;
                hero.weaponKillHistory[hero.weapon->getName()]++;
            }
            return;
        }

        hero.hp -= enemy.strength;
        std::cout << enemy.name << " hits back for " << enemy.strength
                  << " damage. Your HP: " << std::max(0, hero.hp) << "\n";
    }

    if (hero.hp <= 0) {
        std::cout << "You were defeated!\n";
    }
}

std::vector<Enemy> createEnemyList() {
    return {
        Enemy("Goblin", 5, 2, 300, 30),
        Enemy("Orc", 10, 4, 500, 60),
        Enemy("Troll", 15, 5, 700, 80),
        Enemy("KingApe", 20, 8, 1000, 100),
        Enemy("Dragon", 30, 12, 1500, 200),
        Enemy("God!!!", 50, 20, 5000, 1000)
    };
}

int main() {
    Database::init();
    std::vector<Enemy> enemies = createEnemyList();
    Hero hero("Default");

    std::cout << "0: New Hero\n1: Load Hero\n2: Stats\nChoose: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 0) {
        std::string name;
        std::cout << "Enter hero name: ";
        std::getline(std::cin, name);
        hero = Hero(name);
        Database::saveHero(hero);
    } else if (choice == 1) {
        std::string name;
        std::cout << "Enter hero name to load: ";
        std::getline(std::cin, name);
        if (!Database::loadHero(name, hero)) {
            std::cout << "Hero not found.\n";
            return 1;
        }
    } else if (choice == 2) {
        std::vector<Hero> allHeroes = Database::getAllHeroes();

        std::cout << "\n=== Hero Stats ===\n";
        for (const Hero& h : allHeroes) {
            std::cout << h.name << " - Total kills: " << h.totalKills
                      << ", Weapon kills: " << h.weaponKills << "\n";
        }

        std::map<std::string, std::pair<std::string, int>> weaponStats;

        for (const Hero& h : allHeroes) {
            for (const auto& [weaponName, kills] : h.weaponKillHistory) {
                if (weaponStats.find(weaponName) == weaponStats.end() ||
                    kills > weaponStats[weaponName].second) {
                    weaponStats[weaponName] = { h.name, kills };
                }
            }
        }

        std::cout << "\n=== Weapon Stats ===\n";
        for (const auto& [weaponName, entry] : weaponStats) {
            std::cout << weaponName << " - Best used by: " << entry.first
                      << " with " << entry.second << " kills\n";
        }

        return 0;
    }

    while (true) {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1: Fight enemy\n2: Enter dungeon\n0: Save and exit\n";
        int action;
        std::cin >> action;
        std::cin.ignore();

        if (action == 0) {
            Database::saveHero(hero);
            std::cout << "Game saved. Goodbye!\n";
            break;
        } else if (action == 1) {
            std::cout << "Choose enemy:\n";
            for (size_t i = 0; i < enemies.size(); ++i) {
                std::cout << i << ": " << enemies[i].name << "\n";
            }
            int enemyIndex;
            std::cin >> enemyIndex;
            std::cin.ignore();
            if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
                fightEnemy(hero, enemies[enemyIndex], true);
                Database::saveHero(hero);
            }
        } else if (action == 2) {
            std::cout << "Dungeon types:\n1: Custom Dungeon\n2: Hardcore Dungeon\nChoose: ";
            int dungeonType;
            std::cin >> dungeonType;
            std::cin.ignore();

            std::vector<Enemy> dungeonEnemies;
            std::string dungeonName = "Unknown Dungeon";
            int bonusGold = 0;

            if (dungeonType == 1) {
                std::cout << "Choose enemy type:\n";
                for (size_t i = 0; i < enemies.size(); ++i) {
                    std::cout << i << ": " << enemies[i].name << "\n";
                }
                int enemyIndex;
                std::cin >> enemyIndex;
                std::cin.ignore();
                if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
                    for (int i = 0; i < 5; ++i)
                        dungeonEnemies.push_back(enemies[enemyIndex]);
                    dungeonName = enemies[enemyIndex].name + " Dungeon";
                    bonusGold = 150;
                } else {
                    continue;
                }
            } else if (dungeonType == 2) {
                dungeonEnemies = enemies;
                dungeonName = "Hardcore Dungeon";
                bonusGold = 300;
            } else {
                continue;
            }

            Dungeon dungeon(dungeonName, dungeonEnemies, bonusGold);
            dungeon.enter(hero);
            Database::saveHero(hero);
        }
    }

    return 0;
}
