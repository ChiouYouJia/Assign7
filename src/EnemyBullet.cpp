#include "EnemyBullet.h"

ebullet::ebullet(const Position & pos, const Icon& icon) : Bullet(pos, icon){
    _type = ObjectType::eBullet;
    _followtimes = 6;
}

void ebullet::update() {
    
}

static int sign(int v) {
    return (v > 0) - (v < 0);
}

void ebullet::followPlayer(int px, int py) {
    if (_followtimes > 0) {
        int x = _pos.x();
        int y = _pos.y();
        int dx = px - x + 1;

        int moveX = sign(dx);
        const int moveY = 1;

        move(moveX, moveY);
        _followtimes--;
    } else {
        move(0, 1);
    }
    
}

void ebullet::move(int dx, int dy) {
    _pos.x() = _pos.x() + dx;
    _pos.y() = _pos.y() + dy;

}

bool ebullet::outOfWindow() {
    if (_pos.y() > GAME_WINDOW_HEIGHT - 1) {
        return true;
    } else {
        return false;
    }
}

void ebullet::onCollision(ICollider *other) {
	auto* player = dynamic_cast<PlayerObject*>(other);
    player->setLife();
    player->setIcon();
}

bool ebullet::intersect(ICollider *other) {
    auto* player = static_cast<PlayerObject*>(other);
    if (!player) return false;

    int bx = _pos.x();
    int by = _pos.y();

    int px = player->getPosition().x();
    int py = player->getPosition().y();

    return (bx == px || bx == px + 1 || bx == px + 2) && by == py;

}