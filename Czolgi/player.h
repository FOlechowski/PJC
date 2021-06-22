#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include "tank.h"
#include <QString>
#include "obstacles.h"
#include "game.h"
#include "map.h"

class Game;
class Map;

class Player : public Tank
{
    Q_OBJECT

public:
    Player();
    ~Player();

    void setPlayerName(QString Pname);
    void shot();
    bool keyA, keyW, keyD, keyS, keySpace = false, key1 = false, key2 = false;
    void setPointerToView(QGraphicsView *view);
    void setPointerToMap(Map *map);
    void savePlayer(QFile *file);
    void getPointerToGame(Game* game);
    void updateHpBar();
    void updateReloadBar();
    void updateAmmo();
    bool getAmmo();
    void setAPshells(int number);
    void setHEshells(int number);
    void setAP();
    void setHE();
    int getAP();
    int getHE();
    float getArmor();
    void changeRotateAngle(int newAngle);
    int getInitHp();

    void loadPlayer(int hp, int dmg, float armor, int b, int eb, int rtime, int spd, int tr, int eng);

public slots:

private:

    void addPlayerTextures();
    void moveForward(qreal m_distance, int m_angle);
    void moveBackward(qreal m_distance, int m_angle);
    void turnLeft(int &m_angle);
    void turnRight(int &m_angle);
    void upgradeSpeed();
    void upgradeTrack();
    void upgradeArmor();
    bool checkCol();
    bool outOfMap();

    QGraphicsView *view = nullptr;
    Map *map = nullptr;
    QString name;
    Game* game;
    bool front_hit, back_hit, right_hit, left_hit = false;
    int rotate = 0;
    int APShells = 25;               //number of bullets
    int HEShells = 25;               //number of bullets
    bool APisloaded = true;          //false means HE is loaded
    //numbers of upgrades
    int tracks = 0;
    int engine = 0;
    int init_hp = 300;

private slots:
    void movePlayer();
};

#endif // PLAYER_H
