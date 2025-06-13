#include "Enemy.h"
#include "environment.h"

Enemy::Enemy(const Position & pos, const Icon& icon) {
    _pos = pos;
    _icon = icon;
    _type = ObjectType::Enemy;
    _enable = false;
}
void Enemy::update() {
    
}

void Enemy::move(int dx, int dy) {
    int newX = _pos.x() + dx;
    int newY = _pos.y() + dy;

    if (newX >= 0 && newX < GAME_WINDOW_WIDTH + 1  - this->getIcon()[0].size() &&
        newY >= 0 && newY < GAME_WINDOW_HEIGHT + 1 - this->getIcon().size()) {
        _pos.x() = newX;
        _pos.y() = newY;
    }
}

void Enemy::setBulletTimer() {
    unsigned seed = std::chrono::high_resolution_clock::now()
                        .time_since_epoch()
                        .count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> rad(-2, 2);
    _EnemyBulletTimer = 7 + rad(gen);
}

int Enemy::getBulletTimer() {
    return _EnemyBulletTimer;
}

void Enemy::minusBulletTimer() {
    _EnemyBulletTimer--;
}

void Enemy::setEnable() {
    _enable = true;
}

bool Enemy::getEnable() {
    return _enable;
}