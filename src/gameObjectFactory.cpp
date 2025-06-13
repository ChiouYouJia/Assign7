// TODO implementation
#include "gameObjectFactory.h"
#include "staticObject.h"
#include "playerObject.h"
#include "bullet.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

using namespace std;
GameObjectFactory& GameObjectFactory::instance() {
    static GameObjectFactory inst;
    return inst;
}

GameObject* GameObjectFactory::create(ObjectType type, const Position& pos, const Icon& icon) const {
    switch (type) {
        case ObjectType::Player:
            return new PlayerObject(pos, icon);
        case ObjectType::Static:
            return new StaticObject(pos, icon);
        case ObjectType::eBullet:
            return new ebullet(pos, icon);
        case ObjectType::pBullet:
            return new pbullet(pos, icon);
        case ObjectType::Enemy:
            return new Enemy(pos, icon);
        default:
            return nullptr;
    }
}