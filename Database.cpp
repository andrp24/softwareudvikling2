#include "Database.h"
#include <sqlite3.h>
#include <iostream>

void Database::initDB() {
    sqlite3* db;
    sqlite3_open("heroes.db", &db);
    const char* sql = "CREATE TABLE IF NOT EXISTS heroes ("
                      "name TEXT PRIMARY KEY, "
                      "hp INT, "
                      "maxHp INT, "
                      "level INT, "
                      "xp INT, "
                      "gold INT, "
                      "strength INT);"; // tilføjet maxHp og strength
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    sqlite3_close(db);
}


void Database::saveHero(const Hero& hero) {
    sqlite3* db;
    sqlite3_open("heroes.db", &db);
    const char* sql = "REPLACE INTO heroes "
                      "(name, hp, maxHp, level, xp, gold, strength) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, hero.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, hero.hp);
    sqlite3_bind_int(stmt, 3, hero.maxHp);
    sqlite3_bind_int(stmt, 4, hero.level);
    sqlite3_bind_int(stmt, 5, hero.xp);
    sqlite3_bind_int(stmt, 6, hero.gold);
    sqlite3_bind_int(stmt, 7, hero.strength);  // NY
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


Hero Database::loadHero(const std::string& name) {
    sqlite3* db;
    sqlite3_open("heroes.db", &db);
    const char* sql = "SELECT hp, maxHp, level, xp, gold, strength FROM heroes WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    Hero hero(name);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        hero.hp = sqlite3_column_int(stmt, 0);
        hero.maxHp = sqlite3_column_int(stmt, 1);
        hero.level = sqlite3_column_int(stmt, 2);
        hero.xp = sqlite3_column_int(stmt, 3);
        hero.gold = sqlite3_column_int(stmt, 4);
        hero.strength = sqlite3_column_int(stmt, 5);  // NY
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return hero;
}


void Database::listHeroes() {
    sqlite3* db;
    sqlite3_open("heroes.db", &db);
    const char* sql = "SELECT name FROM heroes;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int index = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << index++ << ": " << sqlite3_column_text(stmt, 0) << "\n";
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

