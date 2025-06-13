#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "ObjectType.h"
#include "playerObject.h"
  

class Controller{

public:
    Controller(View&);
    void run();
    void addObject(GameObject*);
    void addplayerBullet(GameObject*);
    void addEnemyBullet(GameObject*);
    void addEnemy(GameObject*);
    void setPlayer(GameObject*);
    void enemyShoot(int px, int py);

    
    ~Controller();
private:

    void handleInput(int);
    void update();

    // Model
    std::vector<GameObject*> _staticObjs;
    std::vector<GameObject*> _enemy;
    std::vector<GameObject*> _playerBullet;
    std::vector<GameObject*> _enemyBullet;
    PlayerObject* _player;
    int _playerCoolDown = 0;
    int _StaticObjLeft = 10;
    createIcons _factory;
    int _timer = 0;
    int _score = 0;

    // View
    View& _view; 
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
