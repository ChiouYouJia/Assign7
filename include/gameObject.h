#pragma once

#include <vector>
#include "unit.h"
#include "icon.h"
#include "ObjectType.h"
#include <iostream>
class GameObject{

public:

    Position getPosition() const;
    Icon getIcon() const;
    virtual void update();
    ObjectType getType() const;
    virtual ~GameObject() = default;
protected:

    Position _pos;
    Icon _icon;
    ObjectType _type;

};
