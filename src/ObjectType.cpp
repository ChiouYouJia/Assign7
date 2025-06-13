#include "ObjectType.h"

Icon createIcons::createPlayer(int life) {
    IconParams greenSquare;
    greenSquare.size = {3, 1};
    greenSquare.color = GREEN;
    greenSquare.ascii = to_string(life);
    Icon square = IconFactory::instance().create(IconType::Block, greenSquare);
    return square;
}

Icon createIcons::createEnemy() {
    IconParams redSquare;
    redSquare.size = {3, 1};
    redSquare.color = RED;
    redSquare.ascii = " ";
    Icon square = IconFactory::instance().create(IconType::Block, redSquare);
    return square;
}

Icon createIcons::createStatic(int life) {
    IconParams blueSquare;
    blueSquare.size = {2, 1};
    blueSquare.color = BLUE;
    blueSquare.ascii = to_string(life);
    Icon square = IconFactory::instance().create(IconType::Block, blueSquare);
    return square;
}

Icon createIcons::createEBullet() {
    IconParams bullet;
    bullet.size = {1, 1};
    bullet.ascii = "。";
    bullet.color = BLACK;
    Icon bulletSquare = IconFactory::instance().create(IconType::Block, bullet);
    return bulletSquare;
}

Icon createIcons::createPBullet() {
    IconParams bullet;
    bullet.size = {1, 1};
    bullet.ascii = "。";
    bullet.color = CYAN;
    Icon bulletSquare = IconFactory::instance().create(IconType::Block, bullet);
    return bulletSquare;
}