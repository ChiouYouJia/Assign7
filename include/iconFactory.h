// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller. 
#pragma once
#include <unordered_map>
#include <functional>
#include "icon.h"
using namespace std;


enum class IconType {
    Block
};

struct IconParams {
    Vec2 size;
    Color color;
    string ascii;
};

class IconFactory {
public:
    static IconFactory& instance();
    Icon create(IconType type, IconParams& params) const;
private:
    IconFactory() = default;
};