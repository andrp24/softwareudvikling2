#ifndef HERO_H
#define HERO_H

#include <string>

class Hero {
private:
    std::string name;
    int xp;
    int level;
    int hitpoints;
    int strength;

public:
    Hero();
    Hero(std::string name, int level, int hitpoints, int strength);

    void saveHero() const;
    bool loadHero(const std::string &heroName);
    void displayStats() const;
};

#endif // HERO_H

