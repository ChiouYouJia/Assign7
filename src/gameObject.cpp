// TODO implementation
#include <vector>
#include "gameObject.h"
#include <iostream>
using namespace std;


Position GameObject::getPosition() const {
    return _pos;
}

Icon GameObject::getIcon() const {
    return _icon;
}

void GameObject::update() {}

ObjectType GameObject::getType() const {
    return _type;
}



