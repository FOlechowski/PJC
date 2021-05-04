#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QDebug>
#include "player.h"
#include "tank.h"

#define VERT 'v'
#define HORIZON 'h'
#define GUARD 'g'

class Enemy : public Tank
{
    Q_OBJECT
public:

    Enemy();

    void holdPos();
    void patrolPathVerticaly(qreal end);
    void patrolPathHorizontaly(qreal end);
    bool check();
    void aim(float angle);
    void setCommand(char comm);

    qreal initx;
    qreal inity;

public slots:
    void move();

protected:

    qreal player_x;
    qreal player_y;

    char command;
    Player *player;
    bool reverso = false;
};

#endif // ENEMY_H
