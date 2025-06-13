#pragma once
#include "bullet.h"
#include "environment.h"
#include <cmath>
#include "staticObject.h" 
#include "playerObject.h"


class ebullet : public Bullet{
public:
    ebullet(const Position & pos, const Icon& icon);
    void update() override;
    void move(int, int) override;
    void followPlayer(int, int);
    bool outOfWindow() override;
    void onCollision(ICollider *other) override;
	bool intersect(ICollider *other) override;
private:
    int _followtimes;
};