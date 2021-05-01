#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include "player.h"
#include "tank.h"

#define HOLD 'h'
#define GUARD 'g'


struct point
{
  qreal x;
  qreal y;
  point *next;
};

class Enemy : public Tank
{
    Q_OBJECT
public:
    Enemy(qreal x, qreal y, Player* pl = NULL);

    void patrol_path(qreal end);
    void hold_pos();
    bool check();
    void set_command(char comm);

    qreal initx;
    qreal inity;

    qreal player_x;
    qreal player_y;

public slots:
    void move();
    void attack();

private:
    Player *player;
    char command;

    bool reverso = false;
};

#endif // ENEMY_H
