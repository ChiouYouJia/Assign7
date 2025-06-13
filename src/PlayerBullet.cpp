#include "PlayerBullet.h"


pbullet::pbullet(const Position & pos, const Icon& icon) : Bullet(pos, icon){
    _type = ObjectType::pBullet;
}

void pbullet::update() {
    move(0, -1);
}

void pbullet::move(int dx, int dy) {
    _pos.x() = _pos.x() + dx;
    _pos.y() = _pos.y() + dy;

}

bool pbullet::outOfWindow() {
    if (_pos.y() < 1) {
        return true;
    } else {
        return false;
    }
}

void pbullet::onCollision(ICollider *other) {
	auto* otherObj = dynamic_cast<StaticObject*>(other);
    otherObj->minusLife();
    otherObj->setIcon();
}

bool pbullet::intersect(ICollider *other) {
    auto* staticObj = static_cast<StaticObject*>(other);
    if (!staticObj) return false;

    int bx = _pos.x();
    int by = _pos.y();

    int sx = staticObj->getPosition().x();
    int sy = staticObj->getPosition().y();

    return (bx == sx || bx == sx + 1) && by == sy;

}

