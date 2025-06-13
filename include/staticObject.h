#pragma once

#include "gameObject.h"
#include "collider.h"
#include "ObjectType.h"

class StaticObject : public GameObject, public ICollider {
public:
    StaticObject(const Position & pos, const Icon& icon);
    int getLife();
    void update() override;
    bool intersect(ICollider *) override;
    void onCollision(ICollider *) override;
    void minusLife();
    void setIcon();
private:
    int _life;
    createIcons _factory;
};