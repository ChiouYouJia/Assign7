#include "staticObject.h"

StaticObject::StaticObject(const Position & pos, const Icon& icon) {
    _pos = pos;
    _icon = icon;
    _life = 2;
    _type = ObjectType::Static;
}

void StaticObject::update(){};

int StaticObject::getLife(){
    return _life;
};

void StaticObject::minusLife() {
    _life--;
}

void StaticObject::setIcon() {
    Icon temp = _factory.createStatic(_life);
    _icon = temp;
}

void StaticObject::onCollision(ICollider *other) {}

bool StaticObject::intersect(ICollider *other) {
    return true;
}