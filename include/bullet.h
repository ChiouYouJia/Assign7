#pragma once
#include "gameObject.h"
#include "collider.h"

class Bullet : public GameObject, public ICollider{
public:
    Bullet(const Position & pos, const Icon& icon);
    void update() override;
    virtual void move(int dx, int dy) = 0;
    virtual bool outOfWindow() = 0;

    ~Bullet() = default;
};