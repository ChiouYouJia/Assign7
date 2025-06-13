#pragma once
#include "icon.h"
#include "iconFactory.h"

enum class ObjectType {
    Static,
    Player,
    eBullet,
    pBullet,
    Enemy
};

class createIcons {
public:
    Icon createEBullet();

    Icon createPBullet();

    Icon createPlayer(int);

    Icon createEnemy();

    Icon createStatic(int);

};