// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 
#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include "ObjectType.h"
#include "gameObject.h"

using namespace std;

class GameObjectFactory {
public:
    
    static GameObjectFactory& instance();
    
    GameObject* create(ObjectType type, const Position& pos, const Icon& icon) const;

private:
    GameObjectFactory() = default;
    
};