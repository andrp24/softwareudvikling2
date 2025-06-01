#ifndef DATABASE_H
#define DATABASE_H

#include "Hero.h"
#include <vector>

class Database {
public:
    static void init();
    static void saveHero(const Hero& hero);
    static bool loadHero(const std::string& name, Hero& hero);
    static std::vector<Hero> getAllHeroes();
};

#endif

