#include "Database.h"
#include <sqlite3.h>
#include <iostream>

void Database::init() {
    sqlite3* db;
    if (sqlite3_open("game.db", &db)) {
        std::cerr << "Can't open DB\n";
        return;
    }

    const char* createHeroTable =
        "CREATE TABLE IF NOT EXISTS heroes ("
        "name TEXT PRIMARY KEY,"
        "hp INTEGER,"
        "maxHp INTEGER,"
        "level INTEGER,"
        "xp INTEGER,"
        "gold INTEGER,"
        "strength INTEGER,"
        "totalKills INTEGER,"
        "weaponKills INTEGER"
        ");";

    sqlite3_exec(db, createHeroTable, nullptr, nullptr, nullptr);

    const char* createKillsTable =
        "CREATE TABLE IF NOT EXISTS weapon_kills ("
        "hero_name TEXT,"
        "weapon_name TEXT,"
        "kills INTEGER,"
        "PRIMARY KEY (hero_name, weapon_name)"
        ");";

    sqlite3_exec(db, createKillsTable, nullptr, nullptr, nullptr);

    sqlite3_close(db);
}

void Database::saveHero(const Hero& hero) {
    sqlite3* db;
    sqlite3_open("game.db", &db);

    const char* saveHeroSql =
        "REPLACE INTO heroes "
        "(name, hp, maxHp, level, xp, gold, strength, totalKills, weaponKills) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, saveHeroSql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, hero.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, hero.hp);
    sqlite3_bind_int(stmt, 3, hero.maxHp);
    sqlite3_bind_int(stmt, 4, hero.level);
    sqlite3_bind_int(stmt, 5, hero.xp);
    sqlite3_bind_int(stmt, 6, hero.gold);
    sqlite3_bind_int(stmt, 7, hero.strength);
    sqlite3_bind_int(stmt, 8, hero.totalKills);
    sqlite3_bind_int(stmt, 9, hero.weaponKills);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to save hero.\n";
    }

    sqlite3_finalize(stmt);

    // Save weapon kills
    const char* insertKill = "REPLACE INTO weapon_kills (hero_name, weapon_name, kills) VALUES (?, ?, ?);";
    sqlite3_stmt* killStmt;
    sqlite3_prepare_v2(db, insertKill, -1, &killStmt, nullptr);

    for (const auto& [weapon, kills] : hero.weaponKillHistory) {
        sqlite3_bind_text(killStmt, 1, hero.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(killStmt, 2, weapon.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(killStmt, 3, kills);
        sqlite3_step(killStmt);
        sqlite3_reset(killStmt);
    }

    sqlite3_finalize(killStmt);
    sqlite3_close(db);
}

bool Database::loadHero(const std::string& name, Hero& hero) {
    sqlite3* db;
    sqlite3_open("game.db", &db);

    const char* sql = "SELECT * FROM heroes WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        hero.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        hero.hp = sqlite3_column_int(stmt, 1);
        hero.maxHp = sqlite3_column_int(stmt, 2);
        hero.level = sqlite3_column_int(stmt, 3);
        hero.xp = sqlite3_column_int(stmt, 4);
        hero.gold = sqlite3_column_int(stmt, 5);
        hero.strength = sqlite3_column_int(stmt, 6);
        hero.totalKills = sqlite3_column_int(stmt, 7);
        hero.weaponKills = sqlite3_column_int(stmt, 8);
        found = true;
    }
    sqlite3_finalize(stmt);

    // Load weapon kills
    const char* loadKills = "SELECT weapon_name, kills FROM weapon_kills WHERE hero_name = ?;";
    sqlite3_stmt* loadStmt;
    sqlite3_prepare_v2(db, loadKills, -1, &loadStmt, nullptr);
    sqlite3_bind_text(loadStmt, 1, name.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(loadStmt) == SQLITE_ROW) {
        std::string weapon = reinterpret_cast<const char*>(sqlite3_column_text(loadStmt, 0));
        int kills = sqlite3_column_int(loadStmt, 1);
        hero.weaponKillHistory[weapon] = kills;
    }
    sqlite3_finalize(loadStmt);

    sqlite3_close(db);
    return found;
}

std::vector<Hero> Database::getAllHeroes() {
    sqlite3* db;
    sqlite3_open("game.db", &db);

    const char* sql = "SELECT * FROM heroes;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    std::vector<Hero> heroes;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Hero h(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        h.hp = sqlite3_column_int(stmt, 1);
        h.maxHp = sqlite3_column_int(stmt, 2);
        h.level = sqlite3_column_int(stmt, 3);
        h.xp = sqlite3_column_int(stmt, 4);
        h.gold = sqlite3_column_int(stmt, 5);
        h.strength = sqlite3_column_int(stmt, 6);
        h.totalKills = sqlite3_column_int(stmt, 7);
        h.weaponKills = sqlite3_column_int(stmt, 8);

        // Load weapon kills for each hero
        const char* loadKills = "SELECT weapon_name, kills FROM weapon_kills WHERE hero_name = ?;";
        sqlite3_stmt* loadStmt;
        sqlite3_prepare_v2(db, loadKills, -1, &loadStmt, nullptr);
        sqlite3_bind_text(loadStmt, 1, h.name.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(loadStmt) == SQLITE_ROW) {
            std::string weapon = reinterpret_cast<const char*>(sqlite3_column_text(loadStmt, 0));
            int kills = sqlite3_column_int(loadStmt, 1);
            h.weaponKillHistory[weapon] = kills;
        }
        sqlite3_finalize(loadStmt);

        heroes.push_back(h);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return heroes;
}

