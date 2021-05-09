#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QDebug>
#include <QTimer>
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
    void followPlayer();

    qreal initx;
    qreal inity;

    bool timer_was_set = false;

public slots:
    void move();
    void comeBack();

protected:
    char command;
    Player *player;

private:
    QTimer *watchdog = new QTimer(this);

    qreal lastPosx = 0;
    qreal lastPosy = 0;

    qreal player_lastx;
    qreal player_lasty;

    bool reverso = false;
    bool was_spotted = false;
};

#endif // ENEMY_H
