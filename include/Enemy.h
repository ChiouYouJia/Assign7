#pragma once
#include "gameObject.h"
#include "collider.h"
#include <random>
#include <chrono>


class Enemy : public GameObject{
public:
    Enemy(const Position & pos, const Icon& icon);
    void update() override;
    void move(int dx, int dy);
    void setBulletTimer();
    int getBulletTimer();
    void minusBulletTimer();
    void setEnable();
    bool getEnable();
private:
    int _EnemyBulletTimer = 0;
    bool _enable;
};