#include "Enemy.h"

Enemy::Enemy(std::string n, int h, int s, int xp, int gold)
    : name(n), hp(h), strength(s), xpReward(xp), goldReward(gold) {}
