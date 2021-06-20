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
    bool keyA, keyW, keyD, keyS,keySpace = false;
    void setPointerToView(QGraphicsView *view);
    void setPointerToMap(Map *map);
    void savePlayer(QFile *file);

public slots:

private:

    void addPlayerTextures();
    void moveForward(qreal m_distance, int m_angle);
    void moveBackward(qreal m_distance, int m_angle);
    void turnLeft(int &m_angle);
    void turnRight(int &m_angle);
    bool checkCol();

    int bullets = 50;


    QGraphicsView *view = nullptr;
    Map *map = nullptr;
    QString name;

    bool front_hit, back_hit, right_hit, left_hit = false;

private slots:

    void movePlayer();
};

#endif // PLAYER_H
