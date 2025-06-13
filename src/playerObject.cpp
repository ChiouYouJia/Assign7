#include "playerObject.h"
#include "environment.h"

PlayerObject::PlayerObject(const Position & pos, const Icon& icon) {
    _pos = pos;
    _icon = icon;
    _type = ObjectType::Player;
    _life = 2;
}
void PlayerObject::update() {
    
}

void PlayerObject::move(int dx, int dy) {
    int newX = _pos.x() + dx;
    int newY = _pos.y() + dy;

    if (newX >= 0 && newX < GAME_WINDOW_WIDTH + 1  - this->getIcon()[0].size() &&
        newY >= 0 && newY < GAME_WINDOW_HEIGHT + 1 - this->getIcon().size()) {
        _pos.x() = newX;
        _pos.y() = newY;
    }
}

void PlayerObject::setLife() {
    _life--;
}

void PlayerObject::setIcon() {
    Icon temp = _factory.createPlayer(_life);
    _icon = temp;
}

void PlayerObject::onCollision(ICollider *other) {}

bool PlayerObject::intersect(ICollider *other) {
    return true;
}

int PlayerObject::getLife() {
    return _life;
}