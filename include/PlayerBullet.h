#pragma once
#include "bullet.h"
#include "environment.h"
#include "staticObject.h"

class pbullet : public Bullet{
public:
    pbullet(const Position & pos, const Icon& icon);
    void update() override;
    void move(int, int) override;
    bool outOfWindow() override;
    void onCollision(ICollider *other) override;
	bool intersect(ICollider *other) override;
};