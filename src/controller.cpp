#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <random>
#include <chrono>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"
#include "playerObject.h"
#include "staticObject.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Enemy.h"



Controller::Controller(View& view) : _view(view){
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    // init state
    int input = -1;
    clock_t start, end;
    
    // Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if (input==27){
            break;
        } else if (_score == WIN_SCORE){
            cout << "You win" << endl;
            break;
        } else if (_player->getLife() == 0) {
            cout << "You lose" << endl;
            break;
        }

        this->handleInput(input);

        _view.resetLatest();
        //更新StaticObjs畫面
        for (GameObject* obj : _staticObjs) 
        {
            obj->update();
            _view.updateGameObject(obj);
        }
        //刪掉生命為零的，並補上一個
        GameObject* staticBlock;
        unsigned seed = std::chrono::high_resolution_clock::now()
                        .time_since_epoch()
                        .count();
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> posX(1, GAME_WINDOW_WIDTH - 3);
        std::uniform_int_distribution<> posY(2, 9);
        
        for (int i = int(_staticObjs.size()) - 1; i >= 0; --i) {
            StaticObject* staticObj =  static_cast<StaticObject*>(_staticObjs[i]);
            if (staticObj->getLife() == 0) {
                delete staticObj;
                _staticObjs.erase(_staticObjs.begin() + i);
                _StaticObjLeft--;
                _score++;
            }
        }

        while (_StaticObjLeft < 10) {
           int x = posX(gen), y = posY(gen);
            staticBlock = GameObjectFactory::instance().create(ObjectType::Static, Position{x, y}, _factory.createStatic(2));
            _staticObjs.push_back(staticBlock);
            _StaticObjLeft++;
        }
        int cnt = 0;
        for (GameObject* e : _enemy) {
            Enemy* enemy = static_cast<Enemy*>(e);
            if (_timer == 0 && cnt == 2) {
                enemy->setEnable();
            } else if (_timer == 40 && (cnt == 0 || cnt == 4) ) {
                enemy->setEnable();
            } else if (_timer == 80 && (cnt == 1 || cnt == 3) ) {
                enemy->setEnable();
            }
            enemy->update();
            if (enemy->getEnable()) {
                if (enemy->getBulletTimer() == 0){
                    enemyShoot(enemy->getPosition().x(), enemy->getPosition().y() + 1);
                    enemy->setBulletTimer();
                } else {
                    enemy->minusBulletTimer();
                }
                _view.updateGameObject(e);
            }
            cnt++;
        }

        for (GameObject* pb : _playerBullet) {
            pbullet* pbu = static_cast<pbullet*>(pb);
            pbu->update();
            _view.updateGameObject(pb);
        }
        
        for (int i = int(_playerBullet.size()) - 1; i >= 0; --i) {
            pbullet* pb =  static_cast<pbullet*>(_playerBullet[i]);
            if (pb->outOfWindow()) {
                delete pb;
                _playerBullet.erase(_playerBullet.begin() + i);
            }
        }

        for (GameObject* eb : _enemyBullet) {
            ebullet* ebu = static_cast<ebullet*>(eb);
            ebu->followPlayer(_player->getPosition().x(), _player->getPosition().y());
            _view.updateGameObject(eb);
        }

        for (int i = int(_enemyBullet.size()) - 1; i >= 0; --i) {
            ebullet* eb =  static_cast<ebullet*>(_enemyBullet[i]);
            if (eb->outOfWindow()) {
                delete eb;
                _enemyBullet.erase(_enemyBullet.begin() + i);
            }
        }
        update();
        _player->update();
        _view.updateGameObject(_player);

        _view.render();

        _timer = (_timer + 1) % 120;
        if (_playerCoolDown > 0) _playerCoolDown--;
        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 1000); // 0.1 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
        cout << "Score : " << _score << endl;
    }

}



void Controller::handleInput(int keyInput){

    // If there is no input, do nothing.
    if(keyInput==-1)return;
    

    // TODO 
    // handle key events.
    if (!_player) return; 
    if (keyInput == 'w') { //shoot
        if (_playerCoolDown == 0) {
            GameObject* bullet = GameObjectFactory::instance().create(ObjectType::pBullet, Position{_player->getPosition().x() + 1, _player->getPosition().y()}, _factory.createPBullet());
            _playerBullet.push_back(bullet);
            _playerCoolDown = 3;
        }
    } else if (keyInput == 'd') {
        _player->move(1, 0);
    } else if (keyInput == 'a') {
        _player->move(-1, 0);
    }
}


void Controller::update(){
    ICollider* castPlayer = static_cast<ICollider*>(_player);
    for (auto it = _enemyBullet.begin(); it != _enemyBullet.end(); ) {
        ebullet* castEbullet = static_cast<ebullet*>(*it);

        bool collided = false;
        if (castEbullet->intersect(castPlayer)) {
            
            collided = true;
            castEbullet->onCollision(castPlayer);
        }

        if (collided) {
            delete *it; // 釋放記憶體
            it = _enemyBullet.erase(it); // 移除指標並取得下一個 iterator
        } else {
            ++it;
        }
    }

    for (auto it = _playerBullet.begin(); it != _playerBullet.end(); ) {
        pbullet* castPbullet = static_cast<pbullet*>(*it);
        bool collided = false;

        for (auto* objB : _staticObjs) {
            StaticObject* castB = static_cast<StaticObject*>(objB);
            if (castPbullet && castPbullet->intersect(castB)) {
                collided = true;
                castPbullet->onCollision(castB);
                break;
            }
        }

        if (collided) {
            delete *it; // 釋放記憶體
            it = _playerBullet.erase(it); // 移除指標並取得下一個 iterator
        } else {
            ++it;
        }
    }
}

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

void Controller::addObject(GameObject* obj) {
    _staticObjs.push_back(obj);
}

void Controller::addplayerBullet(GameObject* obj) {
    _playerBullet.push_back(obj);
}

void Controller::addEnemyBullet(GameObject* obj) {
    _enemyBullet.push_back(obj);
}

void Controller::addEnemy(GameObject* obj) {
    _enemy.push_back(obj);
}

void Controller::setPlayer(GameObject* obj) {
    _player = static_cast<PlayerObject*>(obj);
}

void Controller::enemyShoot(int px, int py) {
    GameObject* bullet = GameObjectFactory::instance().create(ObjectType::eBullet, Position{px + 1, py}, _factory.createEBullet());
    _enemyBullet.push_back(bullet);
}

Controller::~Controller() {
    
}