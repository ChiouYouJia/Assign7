#pragma once
#include "gameObject.h"
#include "collider.h"
#include "ObjectType.h"

class PlayerObject : public GameObject, public ICollider {
public:
    PlayerObject(const Position & pos, const Icon& icon);
    void update() override;
    void move(int dx, int dy);
    bool intersect(ICollider *) override;
    void onCollision(ICollider *) override;
    int getLife();
    void setLife();
    void setIcon();
private:
    createIcons _factory;
    int _life;
};