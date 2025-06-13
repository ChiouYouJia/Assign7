#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"
#include "iconFactory.h"
#include "gameObjectFactory.h"
#include "environment.h"
#include "ObjectType.h"
/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << std::endl << std::endl;
}




int main(){
    // TODO 
    // Integrate the Simple MVC Pattern to run the program.
    View GUI;
    Controller control(GUI);
    
    createIcons Factory;

    GameObject* player = GameObjectFactory::instance().create(ObjectType::Player, Position{GAME_WINDOW_WIDTH / 2, GAME_WINDOW_HEIGHT - 2}, Factory.createPlayer(2));
    control.setPlayer(player); //綠色可操作方塊

    for (int i = 1; i <= 5; i++) {
        GameObject* Enemy = GameObjectFactory::instance().create(ObjectType::Enemy, Position{GAME_WINDOW_WIDTH / 6 * i, 0}, Factory.createEnemy());
        control.addEnemy(Enemy); //Enemy
    }


    
    GameObject* staticBlock;
    unsigned seed = std::chrono::high_resolution_clock::now()
                        .time_since_epoch()
                        .count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> posX(1, GAME_WINDOW_WIDTH - 3);
    std::uniform_int_distribution<> posY(2, 8);
    for (int i = 1; i <= 10; i++) {
        int x = posX(gen), y = posY(gen);
        staticBlock = GameObjectFactory::instance().create(ObjectType::Static, Position{x, y}, Factory.createStatic(2));
        control.addObject(staticBlock);
    }
    

    control.run();

    // TODO
    // change to your student ID.
    PrintMyID("113703030");
}
