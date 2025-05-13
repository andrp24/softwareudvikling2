#include "HeroManager.h"
#include <iostream>

void HeroManager::mainMenu() {
    int choice;
    std::cout << "===== Main Menu =====\n";
    std::cout << "1. Create New Hero\n";
    std::cout << "2. Load Existing Hero\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        createHero();
        break;
    case 2:
        loadHero();
        break;
    case 3:
        std::cout << "Exiting...\n";
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

void HeroManager::createHero() {
    std::string name;
    std::cout << "Enter hero name: ";
    std::cin >> name;

    Hero hero(name, 1, 100, 10);
    hero.saveHero();
    std::cout << "Hero created and saved successfully!\n";
}

void HeroManager::loadHero() {
    std::string name;
    std::cout << "Enter hero name to load: ";
    std::cin >> name;

    Hero hero;
    if (hero.loadHero(name)) {
        hero.displayStats();
    } else {
        std::cout << "Hero not found.\n";
    }
}

